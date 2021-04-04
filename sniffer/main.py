from socket import *
from database import *
import struct
import sys
import datetime
import msvcrt

class sniffer:
	def __init__(self):
		self.HOST = gethostbyname(gethostname())
		self.s = socket(AF_INET, SOCK_RAW, IPPROTO_IP)
		self.s.bind((self.HOST, 0))
		self.s.setsockopt(IPPROTO_IP, IP_HDRINCL, 1)
		self.s.ioctl(SIO_RCVALL, RCVALL_ON)
		self.header, self.data = self.receiveData()
		self.version = self.header[0] >> 4						#IP version
		self.IHL = self.header[0] & 0xF							#Internet Header Length
		self.TOS = tos(self.header[1]) 							#Type Of Service
		self.totalLength = self.header[2] 						# total length of packet ?
		self.ID = self.header[3]
		self.flags = self.header[4]
		self.fragmentOffset = self.header[4] & 0x1FF			#packet number (if a multiple amount is to be received else always 0)
		self.TTL = self.header[5] 								#Time To Live
		self.protocol = self.getProtocol(int(self.header[6]))	#protocol
		self.checksum = self.header[7]
		self.sourceAddress = inet_ntoa(self.header[8])			#from IP
		self.destinationAddress = inet_ntoa(self.header[9])		#to   IP
		if self.protocol == "tcp":
			self.data = tcp(self.data)
		if self.protocol == "udp":
			self.data = udp(self.data)
		if self.protocol == "icmp":
			self.data = icmp(self.data)

	def receiveData(self):
		data = ''
		try:
			data = self.s.recvfrom(65565)
			print(data)
		except timeout:
			print('timed out')
		except:
			print ("An error happened: ")
			sys.exc_info()
		try:
			header = struct.unpack('!BBHHHBBH4s4s' , data[0][:20])
			data = data[0][20:]
		except:
			header = ''
		return header, data
		# return data[0]

	def getProtocol(self,nbr):
		try:
			return protocols[nbr]
		except:
			return nbr

class tos:
	def __init__(self,data):
		self.presence = precedence[data >> 5]
		D = data & 0x10
		D >>= 4
		self.delay = delay[D]
		T = data & 0x8
		T >>= 3
		self.throughput = throughput[T]
		R = data & 0x4
		R >>= 2
		self.reliability = reliability[R]
		M = data & 0x2
		M >>= 1 
		self.cost = cost[M]

class tcp:
	def __init__(self,data):
		self.header = struct.unpack('!HHLLHHHH' , data[:20])
		self.sourcePort = data[0]								#from Port
		self.destinationPort = data[1]							#to Port
		self.sequenceNumber = data[2]
		self.aquitmentNumber = data[3]
		self.flags = self.getflags(data[4])
		self.window = data[5]
		self.sumOfControl = data[6]
		self.pointer = data[7]
		self.options = data[8]
		self.body = data[20:]

	def getflags(self,n):
		return 0


class udp:
	def __init__(self,data):
		self.header = struct.unpack('!HHHH' , data[:8])
		self.sourcePort = data[0]								#from Port
		self.destinationPort = data[1]							#to Port
		self.length = data[2]
		self.checksum = data[3]
		self.body = data[8:]

class icmp:
	def __init__(self,data):
		self.header = struct.unpack('!BBHHH' , data[:8])
		self.type, self.code = self.getType(data[0],data[1])
		self.checksum = data[2]
		self.id = data[3]
		self.sequenceNumber = data[4]
		self.body = data[8:]

	def getType(self,nbr,codeNbr):
		try:
			codeType = typeOfControl[nbr]
			if type(codeType) == dict:
				try:
					codeName = codeType[codeNbr]
				except:
					codeName = codeNbr
				codeType = codeType["name"]
			else:
				codeName = codeNbr
			return codeType, codeName
		except:
			return 'Reserved',codeNbr

packets = []
while True:
	packet = sniffer()
	print(packet.protocol)
	packets.append(packet)