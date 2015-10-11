/*绘图*/


function drawWall(){
	for (var i = 0; i <= numCellW; i++){
		ctx.beginPath();
		ctx.moveTo(i * cellSize, 0);
		ctx.lineTo(i * cellSize, numCellH * cellSize);
		ctx.stroke();
	}
	for (var j = 0; j <= numCellH; j++){
		ctx.beginPath();
		ctx.moveTo(0, j * cellSize);
		ctx.lineTo(numCellW * cellSize, j * cellSize);
		ctx.stroke();
	}
}


function drawACell(i, j){
	if (board[i][j] === 1)
		ctx.fillStyle = "lightblue";
	else if (board[i][j] === 2)
		ctx.fillStyle = "black";
	else
		ctx.fillStyle = "white";
	ctx.beginPath();
	ctx.fillRect(i * cellSize, j * cellSize, cellSize, cellSize);
	//ctx.arc(i * cellSize + cellSize / 2, j * cellSize + cellSize / 2, cellRadius, 0 , 2 * Math.PI, true);
	ctx.closePath();
	ctx.fill();
}


function paint(){
	ctx.clearRect(0, 0, mapWidth, mapHeight);
	for (var i = 0; i < numCellW; i++){
		for (var j = 0; j < numCellH; j++){
			drawACell(i, j);
		}
	}
	drawWall();
}
