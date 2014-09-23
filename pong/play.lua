

-- create image

Player = {}
Player[1] = {x=2, y = 50, speed = 2, score=0, img=
			Image.createEmpty(16,64)}
Player[2] = {x = 462, y = 50, speed = 2.4, score = 0, img = 
			Image.createEmpty(16,64)}

Ball = {x=240, y = math.random(60,180), xspeed = -3, yspeed = 3,
		image = Image.createEmpty(8,8)}

--color the imgs
Player[1].img:clear(Color.new(255,128,64))
Player[2].img:clear(Color.new(128, 0, 64))
Ball.img:clear(Color.new(218, 218, 218))
