/*
*game.js
*__autor__ = wangbb13
*__email__ = wangbinbinsx@gmail.com
*/

/*
*全局变量
*/
var BallChain = [];					//球链数组
var Bullet	  = [];					//发射炮弹的数组
var Battery;						//炮台
var Images    = [];					//所有图片 0:炮台
var Diameter;						//一个小球的直径
var Caliber;						//炮台大小
var BltSpeed  = 5;					//炮弹速度

var Canvas     = document.getElementById('gameCanvas');		 //总体画布
var Cxt = Canvas.getContext('2d');

var CopyCanvas = document.createElement('canvas');		//双缓存
CopyCanvas.width = Canvas.width;
CopyCanvas.height = Canvas.height;
var CCxt = CopyCanvas.getContext('2d');

var Sqrt2	  = 1.414;
//关卡级别 NumOfBalls: 球的数量  Map: 球的轨迹数组
var Levels 	  = [{ NumOfBalls: 20 }, { NumOfBalls: 30 }, { NumOfBalls: 40 }, { NumOfBalls: 50 } ];

var level;							//游戏等级
var numStep   = -1;					//第一个小球走的步数
var interval1;						//画球链的周期函数
var interval2;						//画炮弹的周期函数
var BFinish  = false;				//是否结束
var BSuccess = false;				//是否成功

//音乐
var Sound = {
	background: document.getElementById('backmusic'),
	shoot: document.getElementById('shoot'),
	hit: document.getElementById('hit'),
	display: document.getElementById('display'),
	fail: document.getElementById('fail'),
	vectory: document.getElementById('vectory'),
}


/*
*一个球的类
*x: 初始化位置
*y：初始化位置
*/
function ClassOfBall(x, y, image, style){
	this.image  = image;
	this.style  = style;

	this.posX = x;					//球的当前位置x
	this.posY = y;					//球的当前位置y
	this.move = function(loc){
		this.posX = loc[0];
		this.posY = loc[1];
	};								//移动
	this.getPos = function(){
		return [this.posX, this.posY];
	}

	this.aimX = x;
	this.aimY = y;
	this.setAim = function(loc){
		this.aimX = loc[0];
		this.aimY = loc[1];
	}
	this.getAim = function(){
		return [this.aimX, this.aimY];
	}

	this.index = 0;					//当前坐标的index
	this.canMove = true;			//球能否移动

	this.ifOverflow = function(){
		if (this.posX > Canvas.width || this.posX < 0 || this.posY > Canvas.height || this.posY < 0){
			return true;
		}
		return false;
	};
}

/*
*中心炮台的类
*x: 炮台位置x
*y: 炮台位置y
*/
function ClassOfBattery(x, y, img){	
	this.canvas = document.createElement('canvas');
	this.cxt	= this.canvas.getContext('2d');
	this.canvas.width  = 2 * Diameter + Caliber;
	this.canvas.height = 2 * Diameter + Caliber;
	
	this.image  = img;
	this.posX  = x;
	this.posY  = y;
	this.anG   = 0;

	this.getPos = function(){
		return [this.posX, this.posY];
	}

	this.revole = function(angle){
		this.cxt.translate(this.canvas.width / 2, this.canvas.height / 2);
		this.cxt.rotate(-this.anG);
		this.cxt.rotate(angle);
		this.anG = angle;
		this.cxt.translate(-this.canvas.width / 2, -this.canvas.height / 2);
		this.cxt.clearRect(0, 0, this.canvas.width, this.canvas.height);
		this.cxt.drawImage(this.image, this.canvas.width / 2 - this.image.width / 2, this.canvas.height / 2 - this.image.height / 2);
	}
	this.clearRect = function(){
		this.cxt.clearRect(0, 0, this.canvas.width, this.canvas.height);
	}
}

/*
*windows坐标转为canvas坐标
*/
function WindowToCanvas(canvas, x, y){
	var box = canvas.getBoundingClientRect();
	return [(x - box.left * (canvas.width / box.width)),
			(y - box.top * (canvas.height / box.height))];
}

/*
*BallChain 插入操作 改变位置
*ball: 球
*id：  碰到球的id
*/
function Insert(ball, id){
	ball.index = BallChain[id].index;
	ball.move(Map[level][ball.index]);
	for (var i = id; i >= 0; i--){
		try{
			BallChain[i].index += Step[level];
			BallChain[i].move(Map[level][BallChain[i].index]);
		}
		catch(e){
			BallChain[i].index = Map[level].length - 1;
			BallChain[i].move(Map[level][BallChain[i].index]);
		}
	}
	BallChain.splice(id + 1, 0, ball);
}

/*
*Bullet 从index位置始，删除num个元素
*删除显示，删除数组对应内容
* 加入消除音效,删除效果
*/
function Delete(index, num){
	for (var i = index; i < index + num; i++){
		var loc = BallChain[i].getPos();
		Cxt.clearRect(loc[0] - Diameter / 2, loc[1] - Diameter / 2, Diameter, Diameter);
	}
	BallChain.splice(index, num);
	
	//音乐
	Sound.display.play();
}

/*
*update canmove of BallChain
*id: 消除后，球链前一段最后一个球的id
*/
function UpdateMove(id){
	var temp = id;
	while(temp >= 0){
		BallChain[temp].canMove = false;
		temp--;
	}
}

/*
*up:   前半段与炮弹类型不同的id
*num:  删除元素的个数
函数功能：后退
*/
function Retreat(up, num){
	if (up < 0 || (up + 1) >= BallChain.length){
		return;
	}
	if (BallChain[up].style != BallChain[up + 1].style){
		UpdateMove(up);
		return;
	}

	//前后两球颜色一致
	//后退
	for (var i = up; i >= 0; i--){
		var loc = BallChain[i].getPos();
		Cxt.clearRect(loc[0] - Diameter / 2, loc[1] - Diameter / 2, Diameter, Diameter);
		BallChain[i].index -= num * Step[level];
		BallChain[i].move(Map[level][BallChain[i].index]);
	}

	//循环判断是否消除
	var same = 2;
	down = up + 1;
	while(BallChain[up].style == BallChain[down].style){
		for (var i = down + 1; i < BallChain.length; i++){
			if (BallChain[i].style == BallChain[down].style){
				same++;
				down++;
			}
			else {
				break;
			}
		}
		down++;
		for (var i = up - 1; i >= 0; i--){
			if (BallChain[i].style == BallChain[up].style){
				same++;
				up--;
			}
			else{
				break;
			}
		}
		up--;

		//消除并后退
		if (down - up - 1 >= 3){
			Delete(up + 1, down - up - 1);
			for (var i = up; i >= 0; i--){
				var loc = BallChain[i].getPos();
				Cxt.clearRect(loc[0] - Diameter / 2, loc[1] - Diameter / 2, Diameter, Diameter);
				BallChain[i].index -= (down - up - 1) * Step[level];
				BallChain[i].move(Map[level][BallChain[i].index]);
			}
		}
		else {
			return;
		}
		if (up < 0){
			return;
		}
		down = up + 1;
	}
}

/*
*撞击响应
*ball: 发射中的球
*id  : 插入前一个球的id
*返回值：true:继续运动，false:无
*/
function ImpactRepond(ball, id){
	var shotStyle = 1;
	var up = id;
	for (; up >= 0; up--){
		if (BallChain[up].style == ball.style){
			shotStyle++;
		}
		else{
			break;
		}
	}
	var down = id + 1;
	for (; down < BallChain.length; down++){
		if (BallChain[down].style == ball.style){
			shotStyle++;
		}
		else {
			break;
		}
	}

	Insert(ball, id);
	if (shotStyle >= 3){
		Delete(up + 1, down - up);
		Retreat(up, down - up);
	}
}

/*
*判断是否结束游戏
*返回值：false 不结束 true 结束
*/
function JudgeIfEnd(){
	if (BallChain[0].index < Map[level].length - 1){
		return false;
	}
	if (BallChain[0].index == Map[level].length - 1 && BallChain[0].canMove == true){
		return true;
	}
	for(var i = 0; i < BallChain.length; i++){
		if (BallChain[i].canMove == false){
			return false;
		}
	}
	return true;
}

/*
*找到第一个能运动的球的id
*/
function FindLastNo(){
	var i;
	for (i = 0; i < BallChain.length; i++){
		if (BallChain[i].canMove){
			break;
		}
	}
	return i;
}

/*
*结束时球链运动函数
*返回 true: 只有一个点 false: 有两个以上
*/
function FinishMove(){
	if (BallChain.length == 1){
		return true;
	}
	for (var i = BallChain.length - 1; i > 0; i--){
		BallChain[i].index = BallChain[i - 1].index;
		BallChain[i].move(BallChain[i - 1].getPos());
	}
	var loc = BallChain[0].getPos();
	Cxt.clearRect(loc[0] - Diameter / 2, loc[1] - Diameter / 2, Diameter, Diameter);
	BallChain.splice(0, 1);
	return false;
}

/*
*画结束动画
*/
function DrawFinish(){
	for (var i = 0; i < BallChain.length; i++){
		var loc = BallChain[i].getPos();
		Cxt.clearRect(loc[0] - Diameter / 2, loc[1] - Diameter / 2, Diameter, Diameter);
	}

	var flag = FinishMove();
	if (flag){
		var loc = BallChain[0].getPos();
		Cxt.clearRect(loc[0] - Diameter / 2, loc[1] - Diameter / 2, Diameter, Diameter);
		BallChain.length = 0;
		return;
	}
	for (var i = 0; i < BallChain.length; i++){
		var loc = BallChain[i].getPos();
		Cxt.drawImage(BallChain[i].image, loc[0] - Diameter / 2, loc[1] - Diameter / 2);
	}

	setTimeout(DrawFinish, 20);
}

/*
*球链运动函数
*/
function NaiveMove(){
	var fisrtCanMove = 0;
	if (BallChain.length == 0){
		BFinish = true;
		BSuccess = true;
		return;
	}
	if (JudgeIfEnd()){
		BFinish = true;
		return;
	}
	else {
		fisrtCanMove = FindLastNo();
		if (fisrtCanMove == BallChain.length){
			UpdateMove(BallChain.length - 1);
			return;
		}
		try{
			BallChain[fisrtCanMove].index++;
			BallChain[fisrtCanMove].move(Map[level][BallChain[fisrtCanMove].index]);
		}
		catch(e){
			BallChain[fisrtCanMove].index = Map[level].length - 1;
			BallChain[fisrtCanMove].move(Map[level][BallChain[fisrtCanMove].index]);
		}
		for (var i = fisrtCanMove + 1; i < BallChain.length; i++){
			try {
				BallChain[i].index = BallChain[i - 1].index - Step[level];
				BallChain[i].move(Map[level][BallChain[i].index]);
			}
			catch (e){
				break;
			}
		}
		//球链接上了
		if (fisrtCanMove != 0){
			for (var i = fisrtCanMove - 1; i >= 0; i--){
				if (BallChain[i].index - BallChain[i + 1].index <= Step[level]){
					BallChain[i].canMove = true;
				}
				else {
					break;
				}
			}
		}
	}
}

/*
*判断该球是否击中球链
*返回 ifHit[0] true: 击中 false: 未击中
*	  ifHit[1] 击中球的id
*/
function JudgeIfHit(ball){
	var loc = ball.getPos();
	for (var i = 0; i < BallChain.length; i++){
		var it = BallChain[i].getPos();
		var x = it[0] - loc[0];
		var y = it[1] - loc[1];
		if (Math.sqrt(x * x + y * y) <= Diameter){
			return [true, i];
		}
	}
	return [false];
}

/*
*炮弹运动函数
*/
function BulletMove(){
	for (var i = 0; i < Bullet.length; i++){
		var now = Bullet[i].getPos();
		var to  = Bullet[i].getAim();
		Bullet[i].move([now[0] + to[0], now[1] + to[1]]);

		var ifHit = JudgeIfHit(Bullet[i]);
		if (ifHit[0]){
			//音乐
			Sound.hit.play();
			ImpactRepond(Bullet[i], ifHit[1]);
			Bullet.splice(i, 1);
		}
		if (Bullet[i].ifOverflow()){
			var loc = Bullet[i].getPos();
			Cxt.clearRect(loc[0] - Diameter / 2, loc[1] - Diameter / 2, Diameter, Diameter);
			Bullet.splice(i, 1);
		}
	}
}

/*
*画球链
*/
function DrawBallChain(){
	for (var i = 0; i < BallChain.length; i++){
		var loc = BallChain[i].getPos();
		Cxt.clearRect(loc[0] - Diameter / 2, loc[1] - Diameter / 2, Diameter, Diameter);
	}
	NaiveMove();
	if (BSuccess){
		$('#success').show();
		clearInterval(interval1);

		//音乐
		Sound.vectory.play();
	}
	else if (BFinish){
		DrawFinish();
		$('#faillayer').show();
		clearInterval(interval1);
		
		//音乐
		Sound.fail.play();
	}
	for (var i = 0; i < BallChain.length; i++){
		var loc = BallChain[i].getPos();
		Cxt.drawImage(BallChain[i].image, loc[0] - Diameter / 2, loc[1] - Diameter / 2);
	}
}

/*
*画炮弹
*/
function DrawBullet(){
	for (var i = 0; i < Bullet.length; i++){
		var loc = Bullet[i].getPos();
		Cxt.clearRect(loc[0] - Diameter / 2, loc[1] - Diameter / 2, Diameter, Diameter);
	}
	BulletMove();
	for (var i = 0; i < Bullet.length; i++){
		var loc = Bullet[i].getPos();
		Cxt.drawImage(Bullet[i].image, loc[0] - Diameter / 2, loc[1] - Diameter / 2);
	}
}


/*
*初始化数据
*/
var all = 0;
var img = [];
function Initial(){
	for (var i = 0; i < 12; i++){
		img[i] = new Image();
		if (i == 0){
			img[i].src = "images/background.png";
		}
		else if (i > 0 && i < 6){
			img[i].src = "images/ball" + i + ".png";
		}
		else if (i > 5 && i < 10){
			img[i].src = "images/map" + (i - 5) + ".png";
		}
		else if (i == 10){
			img[i].src = "images/bullet.png";
		}
		else {
			img[i].src = "images/title.png";
		}
		img[i].onload = function(){
			all++;
			if (all == 12){
				for (var i = 0; i < 12; i++){
					Images[i] = img[i];
				}
				$('body').css("background-image", "url(images/background.png)");
				$('#loading').hide();
				$('#title').append("<img src=\"images/title.png\">");
				$('#start-interface').show();
			}
		};
	}
	Sound.background.play();
}
Initial();

/*
*游戏运行接口
*/
function Play(){
	BFinish = false;
	BSuccess = false;
	Diameter = Images[1].width;
	Caliber  = Images[10].width;
	for (var i = 0; i < Levels[level].NumOfBalls; i++){
		var style = Math.ceil(Math.random() * 5);
		var ball = new ClassOfBall(Canvas.width + Diameter, Canvas.height + Diameter, Images[style], style);
		BallChain.push(ball);
	}
	Battery = new ClassOfBattery(Canvas.width / 2, Canvas.height / 2, Images[10]);

	//画炮台
	var centerx = Canvas.width / 2;
	var centery = Canvas.height / 2;
	Cxt.clearRect(centerx - Caliber / 2, centery - Caliber / 2, Caliber, Caliber);
	Battery.revole(0);
	Cxt.drawImage(Battery.canvas, centerx - Caliber / 2, centery - Caliber / 2);
	Battery.clearRect();

	//画炮弹
	var style = Math.ceil(Math.random() * 5);
	var ball = new ClassOfBall(Canvas.width, Canvas.height, Images[style], style);
	ball.move([Canvas.width / 2, Canvas.height / 2]);
	ball.setAim([0, 0]);
	Bullet.push(ball);
	Cxt.clearRect(centerx - Diameter / 2, centery - Diameter / 2, Diameter, Diameter);
	Cxt.drawImage(Bullet[0].image, centerx - Diameter / 2, centery - Diameter / 2);

	//画轨道及小球
	interval1 = setInterval("DrawBallChain()", 100);
	interval2 = setInterval("DrawBullet()", 10);
}


//事件响应
/*
*鼠标点击，发射炮弹
*/
$('#gameCanvas').mousedown(function(e){
	//音乐
	Sound.shoot.play();
	var loc = WindowToCanvas(Canvas, e.clientX, e.clientY);
	var now = [Canvas.width / 2, Canvas.height / 2];
	var to  = [parseInt(loc[0]), parseInt(loc[1])];
	var deltax;
	var deltay;
	if (to[0] == now[0]){
		deltax = 0;
		deltay = Math.abs(to[1] - now[1]) / (to[1] - now[1]) * BltSpeed;
	}
	else if (to[1] == now[1]){
		deltax = Math.abs(to[0] - now[0]) / (to[0] - now[0]) * BltSpeed;
		deltay = 0;
	}
	else {
		var dx = to[0] - now[0];
		var dy = to[1] - now[1];
		var dz = Math.sqrt(dx * dx + dy * dy);
		var alpha = Math.asin(dy / dz);
		if (dy <= 0 && dx <= 0){
			alpha = -(Math.PI + alpha);
		}
		else if (dy >= 0 && dx <= 0){
			alpha = Math.PI - alpha;
		}
		deltax = BltSpeed * Math.cos(alpha);
		deltay = BltSpeed * Math.sin(alpha);
	}
	Bullet[Bullet.length - 1].setAim([deltax, deltay]);	

	var style = Math.ceil(Math.random() * 5);
	var ball = new ClassOfBall(Canvas.width, Canvas.height, Images[style], style);
	ball.move([Canvas.width / 2, Canvas.height / 2]);
	ball.setAim([0, 0]);
	Bullet.push(ball);
	Cxt.clearRect(Canvas.width / 2 - Diameter / 2, Canvas.height / 2 - Diameter / 2, Diameter, Diameter);
	Cxt.drawImage(Bullet[0].image, Canvas.width / 2 - Diameter / 2, Canvas.height / 2 - Diameter / 2);
});

/*
*鼠标移动，旋转炮台
*/
$('#gameCanvas').mousemove(function(e){
	var centerx = Canvas.width / 2;
	var centery = Canvas.height / 2;
	var loc 	= WindowToCanvas(Canvas, e.clientX, e.clientY);
	var cx 		= parseInt(loc[0]);
	var cy 		= parseInt(loc[1]);
	var x 		= cx - centerx;
	var y 		= cy - centery;
	var z		= Math.sqrt(x * x + y * y);
	var angle 	= Math.asin(y / z);
	if (y <= 0 && x <= 0){
		angle = -(Math.PI + angle);
	}
	if (y >= 0 && x <= 0){
		angle = Math.PI - angle;
	}

	Cxt.clearRect(centerx + Diameter / 2, centery + Diameter / 2, Caliber, Caliber);
	Battery.revole(angle);
	Cxt.drawImage(Battery.canvas, centerx - Caliber / 2, centery - Caliber / 2);
	Battery.clearRect();
});

//开始事件
$('.startBtn').click(function(){
	$('#selectlevel').show();
});

//帮助事件
$('.helpBtn').click(function(){
	$('#shade').show();
	$('#itdlayer').show();
});

//说明弹层返回主菜单
$('#returnstart').click(function(){
	$('#shade').hide();
	$('#itdlayer').hide();
	$('#start-interface').show();
});

//游戏界面返回主菜单
$('#returnmain').click(function(){
	Sound.fail.pause();
	$('#faillayer').hide();
	$('#run-interface').hide();
	$('#start-interface').show();
});

//再玩一次
$('#tryagain').click(function(){
	Sound.fail.pause();
	BallChain.length = 0;
	Bullet.length    = 0;
	clearInterval(interval1);
	clearInterval(interval2);
	$('#faillayer').hide();
	Play();
});

//下一关
$('#nextlevel').click(function(){
	Sound.vectory.pause();
	level = (level + 1) % 4;
	clearInterval(interval1);
	clearInterval(interval2);
	BallChain.length = 0;
	Bullet.length    = 0;
	$('#success').hide();
	switch (level){
	case 0:
		$('#subcanvas').css("background-image", "url(images/map1.png)");
		break;
	case 1:
		$('#subcanvas').css("background-image", "url(images/map2.png)");
		break;
	case 2:
		$('#subcanvas').css("background-image", "url(images/map3.png)");
		break;
	case 3:
		$('#subcanvas').css("background-image", "url(images/map4.png)");
		break;
	default:
		break;
	}
	$('#run-interface').show();
	Play();
})

//success again
$('#again').click(function(){
	Sound.vectory.pause();
	clearInterval(interval1);
	clearInterval(interval2);
	$('#success').hide();
	BallChain.length = 0;
	Bullet.length    = 0;
	Play();
})

// success back
$('#backmain').click(function(){
	Sound.vectory.pause();
	$('#success').hide();
	$('#run-interface').hide();
	$('#start-interface').show();
})

//第一关
$('#level1').click(function(){
	level = 0;
	$('#subcanvas').css("background-image", "url(images/map1.png)");
	$('#start-interface').hide();
	$('#run-interface').show();
	$('#selectlevel').hide();
	Play();
});

//第二关
$('#level2').click(function(){
	level = 1;
	$('#subcanvas').css("background-image", "url(images/map2.png)");
	$('#start-interface').hide();
	$('#run-interface').show();
	$('#selectlevel').hide();
	Play();
});

//第三关
$('#level3').click(function(){
	level = 2;
	$('#subcanvas').css("background-image", "url(images/map3.png)");
	$('#start-interface').hide();
	$('#run-interface').show();
	$('#selectlevel').hide();
	Play();
});

//第四关
$('#level4').click(function(){
	level = 3;
	$('#subcanvas').css("background-image", "url(images/map4.png)");
	$('#start-interface').hide();
	$('#run-interface').show();
	$('#selectlevel').hide();
	Play();
});


