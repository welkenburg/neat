import pygame
from pygame.locals import *
import random
pygame.init()


def count(array,element):
	"""
	count the number of time an element apears in a list

	count([0,1,0,2,3,4,0],0)
	>>> 3

	"""
	counter = 0
	for i in array:
		counter += (i == element)
	return counter

class gameboard:
	def __init__(self,bot):
		self.board = [list(["" for i in range(3)]) for j in range(3)]
		self.bot = bot
		self.players = ("x","o")
		self.width = 200*3
		self.height = 200*3
		self.window = pygame.display.set_mode((self.width,self.height))
		self.running = True
		self.turn = 0
		while self.running:
			self.update()
		pygame.quit()

	def fullBoard(self):
		"""
		check if the board is full, if it is, nobody wins
		"""
		for i in self.board:
			for j in i:
				if j == "":
					return False
		print("tie, nobody wins")
		self.running = False
		return True

	def minmax(self):
		if self.playHere((random.randint(0,2),random.randint(0,2)),self.players[1]):
			return
		else:
			self.minmax()

	def win(self,player):
		"""
		check if 3 same signs are aligned, if they are, somebody wins
		"""
		win = False
		for i in range(len(self.board)):
			if count(self.board[i],player) == 3:
				win = True
		for i in range(len(self.board)):
			if count([self.board[0][i],self.board[1][i],self.board[2][i]],player) == 3:
				win = True
		if count([self.board[0][0],self.board[1][1],self.board[2][2]],player) == 3:
			win = True
		if count([self.board[2][0],self.board[1][1],self.board[0][2]],player) == 3:
			win = True
		return win

	def playHere(self,pos,player):
		"""
		make a move at a given position
		"""
		if self.fullBoard():
			return 1
		if self.board[pos[0]][pos[1]] == "":
			self.board[pos[0]][pos[1]] = player
			return 1
		return 0

	def drawRect(self,w,h,x,y,color):
		"""
		draw a rectangle with a width, height, x and y coords and a color
		"""
		s = pygame.Surface((w,h))
		s.fill(color)
		self.window.blit(s, (x,y))

	def update(self):
		"""
		update the screen
		"""

		#quit
		for event in pygame.event.get():
			if event.type == QUIT:
				exit()

			#plays here event
			if event.type == MOUSEBUTTONUP:
				i = event.pos[0] * 3 / self.width
				j = event.pos[1] * 3 / self.height
				if self.playHere((int(i),int(j)),self.players[self.turn%2]):
					if self.win(self.players[self.turn%2]):
						print(f"{self.players[self.turn%2]} wins")
						exit()
					self.turn += 1

			#reset the game
			if event.type == KEYDOWN and event.key == 114:
				self.board = [list(["" for i in range(3)]) for j in range(3)]
				self.turn = 0

		#the bot plays
		if self.turn%2 == 1 and self.bot == True:
			self.minmax()
			if self.win(self.players[self.turn%2]):
				print("bot wins")
				self.running = False
			self.turn += 1

		#background
		self.drawRect(self.width,self.height,0,0,(255,255,255))

		#draw board
		for i in range(len(self.board)):
			rectWidth = self.width/len(self.board)
			rectHeight = self.height/len(self.board[i])
			for j in range(len(self.board[i])):
				if self.board[i][j] == "x":
					self.drawRect(rectWidth,rectHeight,rectWidth*i,rectHeight*j,(0,0,255))
				elif self.board[i][j] == "o":
					self.drawRect(rectWidth,rectHeight,rectWidth*i,rectHeight*j,(255,0,0))
			
		pygame.display.update()

gameboard(True)