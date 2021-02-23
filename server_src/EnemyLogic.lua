MAX_RANGE = 6

function DistanceFromEnemy(enemy_x, enemy_y, player_x, player_y)
	distance1 = math.pow(enemy_x-player_x, 2)
	distance2 = math.pow(enemy_y-player_y, 2)
	total = distance1 + distance2
	return math.sqrt( total )
end


function ProcessSnapshot(snapshot)
	
	data = {}
	enemy_pos_x = snapshot[2].pos_x
	enemy_pos_y = snapshot[2].pos_y
	enemy_direction = snapshot[2].direction
	enemy_range = snapshot[2].range
	enemy_ammo = snapshot[2].ammo

	min_distance = 9999
	for j=1, #snapshot[1] do
		if snapshot[1][j].health > 0 then
			dist = DistanceFromEnemy(enemy_pos_x, enemy_pos_y, snapshot[1][j].pos_x,snapshot[1][j].pos_y )
			if dist < min_distance then
				nearest_id = snapshot[1][j].id
				min_distance = dist
				pos_x = snapshot[1][j].pos_x
				pos_y = snapshot[1][j].pos_y
			end
		end
	end

	angle = (math.atan(enemy_pos_y - pos_y, enemy_pos_x - pos_x) - 3.1416) * 180 / 3.1416
	angle = (angle - enemy_direction)
	if (angle > 180) then
		angle = angle - 360
	elseif (angle <-180) then
		angle = angle + 360
	end


	if enemy_ammo > 0 and enemy_range == 1 then
		response = '2'
	elseif min_distance > MAX_RANGE then
		response = 'd'
	elseif (math.abs(angle) > 4) and ((angle) < 0) then
		response = 'a'
	elseif (math.abs(angle) > 4) then
		response = 'd'
	elseif min_distance > enemy_range then
		response = 'w'
	else 
		response = ' '
	end
	return response

end
