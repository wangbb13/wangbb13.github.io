/*处理游戏逻辑和绘制图形*/
var board, board_copy;
var dom_canvas, dom_div, cxt;
var ceilW = 10, ceilH = 10, ceilRadius = 5, n, m;

var dx = [0, 0, 1, -1, -1, -1, 1, 1];
var dy = [1, -1, 0, 0, 1, -1, -1, 1];

function initial(){		//初始化网格
	dom_canvas = document.getElementById('drawRec');
	dom_div = document.getElementById('divCanvas');
	dom_canvas.width = dom_div.clientWidth;
	dom_canvas.height = dom_div.clientHeight;
	cxt = dom_canvas.getContext('2d');
	n = parseInt(dom_div.clientWidth / ceilW) + 1;
	m = parseInt(dom_div.clientHeight / ceilH) + 1;
	board = new Array(n);
	board_copy = new Array(n);
	for (var i = 0; i < n; i++){
		board[i] = new Array(m);
		board_copy[i] = new Array(m);
	}
	for (var i = 0; i < n; i++){
		for (var j = 0; j < m; j++){
			board[i][j] = Math.round(Math.random());
		}
	}
}

function transform(){		//状态变换
	for (var i = 0; i < n; i++){
		for (var j = 0; j < m; j++){
			var s = 0;
			for (var k = 0; k < 8; k++){
				var x = i + dx[k], y = j + dy[k];
				x = (x + n) % n;
				y = (y + m) % m;
				if (board[x][y])
					s++;
			}
			if (s == 3)
				board_copy[i][j] = 1;
			else if (s != 2)
				board_copy[i][j] = 0;
			else board_copy[i][j] = board[i][j];
		}
	}
	for (var i = 0; i < n; i++)
		for (var j = 0; j < m; j++)
			board[i][j] = board_copy[i][j];
}

function paint(){		//绘图
	cxt.clearRect(0, 0, dom_canvas.clientWidth, dom_canvas.clientHeight);
	for (var i = 0; i < n; i++){
		for (var j = 0; j < m; j++){
			if (board[i][j])
				cxt.fillStyle = "lightblue";
			else
				cxt.fillStyle = "white";
			cxt.beginPath();
			cxt.arc(i * ceilW + ceilW / 2, j * ceilH + ceilH / 2, ceilRadius, 0 , 2 * Math.PI, true);
			cxt.closePath();
			cxt.fill();
		}
	}
}


function gameLoop() {	//定时函数
	paint();
	transform();
	setTimeout(gameLoop, 50);
}

initial();

gameLoop();