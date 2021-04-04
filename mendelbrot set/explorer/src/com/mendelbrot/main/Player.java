package com.mendelbrot.main;

import java.awt.Color;
import java.awt.Graphics;

public class Player extends GameObject{
	
	private Color color;

	public Player(int x, int y, ID id, Color color) {
		super(x,y,id);
		vely = (id == ID.vertical) ? 0 : 4;
		velx = (id == ID.vertical) ? 4 : 0;
		this.color = color;
	}
	
	public void tick() {
		if(id == ID.vertical) {
			if(x >= 640 - 32) velx = -4;
			if(x <= 0) velx = 4;
			x+= velx;
		}
		if(id == ID.horizontal) {
			if(y >= 480 - 46) vely = -4;
			if(y <= 0) vely = 4;
			y+= vely;
		}
	}
	
	public void render(Graphics g) {
		g.setColor(color);
		if (id == ID.vertical)
			g.fillRect(x, y, 10, 640 / 12 * 9);
		if (id == ID.horizontal)
			g.fillRect(x, y, 640, 10);
	}
}
