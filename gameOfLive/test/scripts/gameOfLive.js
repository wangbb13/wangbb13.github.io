/*data and game logic*/
//canvas
var canvas = $('#drawRec')[0];
var ctx = canvas.getContext('2d');

//map
var board;
var board_copy;
var mapWidth = $('#divCanvas')[0].clientWidth;
var mapHeight = $('#divCanvas')[0].clientHeight;
var numCellW;
var numCellH;

//cell
var cellSize = 55;
// var cellRadius = 26;
var cellDensity = 0.5;

//else
var dirx;
var diry;
var refreshRate = 500;
var startFlag = false;
var firstGame = true;
var loop;


function initVariable(mW, mH, cS, cD, rR){
	canvas.width = mW;
	canvas.height = mH;
	numCellW = parseInt(mW / cS);
	numCellH = parseInt(mH / cS);
	cellSize = cS;
	// cellRadius = cellSize / 2 - 1;
	cellDensity = cD;
	refreshRate = rR;

	$('#sizeRg').val(cellSize);
	$('#rateRg').val(refreshRate);
	$('#densityRg').val(cellDensity * 10);
}

function initConst(){	
	dirx = [1, 0, -1, 0, 2, 0, -2, 0];
 	diry = [0, -1, 0, 1, 0, -2, 0, 2];	
}

function initBoard(){
	board = new Array(numCellW);
	board_copy = new Array(numCellW);
	var i, j;
	for (i = 0; i < numCellW; i++){
		board[i] = new Array(numCellH);
		board_copy[i] = new Array(numCellH);
	}
	for (i = 0; i < numCellW; i++){
		for (j = 0; j < numCellH; j++){
			board[i][j] = Math.random() * 0.5 / (1 - cellDensity) < 0.5 ? 0 : 1;
		}
	}
}

function initAll(){
	initVariable(mapWidth, mapHeight, cellSize, cellDensity, refreshRate);
	initConst();
	initBoard();
}

function rules(i, j){
	if (board[i][j] == 2){
		return 2;
	}
	var s = 0, k;
	for (k = 0; k < 8; k++){
		var x = (i + dirx[k] + numCellW) % numCellW;
		var y = (j + diry[k] + numCellH) % numCellH;
		if (board[x][y] === 1){
			s++;
		}
	}
	if (s === 3){
		return 1;
	} else if (s === 2){
		return board[i][j];
	} else {
		return 0;
	}
}

function transform(){
	var i, j;
	for (i = 0; i < numCellW; i++){
		for (j = 0; j < numCellH; j++){
			board_copy[i][j] = rules(i, j);
		}
	}
	for (i = 0; i < numCellW; i++)
		for (j = 0; j < numCellH; j++)
			board[i][j] = board_copy[i][j];
}

function bindEvent(){
	$('#refreshBtn').click(function(){
		cs =$('#sizeRg').val();
		cd = $('#densityRg').val() / 10;
		rr = $('#rateRg').val();
		initVariable(mapWidth, mapHeight, cs, cd, rr);
		initBoard();
		drawWall();
		try{
			clearInterval(loop);
		} catch(e){}
		firstGame = true;
		startFlag = false;
		alert("点击选择墙壁");
		$('#ssBtn').attr('value', '开始');
	});

	$('#ssBtn').click(function(){
		startFlag = !startFlag;
		firstGame = false;
		if (startFlag){
			$('#ssBtn').attr('value', '暂停');
			loop = setInterval(gameLoop, refreshRate);
		}
		else{
			$('#ssBtn').attr('value', '开始');
			clearInterval(loop);
		}
	});

	canvas.addEventListener('click', function(evt){
		if (firstGame){
			var rect = canvas.getBoundingClientRect();
			var mPosx = evt.clientX - rect.left * (canvas.width / rect.width);
			var mPosy = evt.clientY - rect.top * (canvas.height / rect.height);
			var i = Math.floor(mPosx / cellSize);
			var j = Math.floor(mPosy / cellSize);
			board[i][j] = 2;
			drawACell(i, j);
		}
	}, false);
}

function gameLoop() {
	paint();
	transform();
}

initAll();
bindEvent();
drawWall();
alert("点击选择墙壁");