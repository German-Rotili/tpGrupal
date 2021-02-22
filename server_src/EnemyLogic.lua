VALID_RANGE = 2

function DistanceFromEnemy(enemy_x, enemy_y, player_x, player_y)
	distance1 = math.pow(enemy_x-player_x, 2)
	distance2 = math.pow(enemy_y-player_y, 2)
	total = distance1 + distance2
	print("Distance SQ: ", math.sqrt( total ))
	return math.sqrt( total )
end


function ProcessSnapshot(snapshot)
	
	--  snapshot[1] --JUGADORES
	--  snapshot[2] --OBJETOS
	

	--Necesito del enemigo actual:
	--Posicion
	--Angulo
	--??cambio de arma?
	data = {}
	enemy_pos_x = snapshot[2].pos_x
	enemy_pos_y = snapshot[2].pos_y
	enemy_direction = snapshot[2].direction

	print("Enemy x: ",enemy_pos_x)
	print("Enemy y: ",enemy_pos_y)
	print("Enemy dir: ",enemy_direction)

	-- calculo distancia para todos los jugadores: ID - DISTANCE
	
	
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

	print("Nearest x: ",pos_x)
	print("Nearest y: ",pos_y)

	print("Nearest Dist: ", min_distance)


	--angulo entre el jugador y el enemigo
	angle = (math.atan(pos_y - enemy_pos_y, pos_x - enemy_pos_x) - 3.1426) * 180 / 3.1426
	print("Angle: ",angle)
	angle = math.abs(angle) - enemy_direction
	print("Angle Diff: ",angle)
	print("Angle Diff Round: ", math.abs(math.floor(angle)))



	if math.abs(math.floor(angle)) > 10 then
		response = 'd'
		print("angle diff: ",response)
	elseif min_distance > VALID_RANGE then
		response = 'w'
		print("range: ",response)
	else 
		response = ' '
		print("attack: ",response)
	end

	return response

end
