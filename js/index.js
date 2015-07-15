/*
*index.js
*/
var xmlHttp;
var jsonObj;
var imgLimit   = 200;
var imgLoad    = 0;
var imgLoading = 0;
var imgLoadCom = 0;
var imgNumb    = 20;

var jsonCom;
var curId;
var curPage = 1;
var curComs = 0;

var curLongi;
var curLati;


function loadXMLDoc(url, func){
	if (window.XMLHttpRequest){
		xmlHttp = new XMLHttpRequest();
	}
	else {
		xmlHttp = new ActiveXObject("Microsoft.XMLHTTP");
	}
	xmlHttp.onreadystatechange = func;
	xmlHttp.open("GET", url, true);
	xmlHttp.send();
}


function loadData(){
	try{
		loadXMLDoc("/json/data.json", function(){
			if (xmlHttp.readyState == 4){
				if (xmlHttp.readyState==4 && xmlHttp.status==200){
					jsonObj = eval("(" + xmlHttp.responseText + ")");
					while(imgLoad <= 10){
						addOne();
					}
				}
			}
		});
	}
	catch(e){
		addError();
	}
	
}


function loadComment(id, page){
	try{
		loadXMLDoc("/json/comments/" + id + "_" + page + ".json", function(){
			if (xmlHttp.readyState == 4){
				if (xmlHttp.readyState == 4 && xmlHttp.status == 200){
					jsonCom = eval("(" + xmlHttp.responseText + ")");
					addCom(page);
				}
			}
		});
	}
	catch(e){
		return;
	}
}


function addError(){
	if (imgLoad > imgLimit){
		return;
	}

	imgLoad++;
	document.getElementById(imgLoad).innerHTML = '<a><img src=' + "/img/error.jpg" + '></a>'
						+ '<div class="info"></div>';
}


function addOne(){
	if (imgLoad > imgLimit){
		return;
	}

	var picId  = (imgLoad++) % imgNumb;
	var picSrc = jsonObj[picId].picSrc;
	var picPos = '</br>经度：' + jsonObj[picId].picPos[0] 
				+ ' 纬度: ' + jsonObj[picId].picPos[1];
	var dist   = getDistance(jsonObj[picId].picPos[0], jsonObj[picId].picPos[1], curLongi, curLati);
	dist       = parseInt(dist);
	var imgSty = Math.ceil(Math.random() * 3);

	document.getElementById(imgLoad).innerHTML
						= ('<a><img src=' + picSrc + ' class="img-ul' + imgSty
						+ '" onclick="showShade(this.id)" id="' 
						+ (picId + 1) + '"></a>'
						+ '<div class="info">'
						+ '<p>' + '</br>' + '位置信息：'
						+ picPos + '</br>距离您：'
						+ dist + '千米</p></div>');
}


function addLoad(){
	if (imgLoading > imgLimit){
		return;
	}
	var uls = [];
	var minH = Number.MAX_VALUE, minId = 0;
	for (var i = 0; i < 4; i++){
		uls[i] = document.getElementById("ul" + (i + 1));
		if (uls[i].clientHeight <= minH){
			minH = uls[i].clientHeight;
			minId = i;
		}
	}
	elemNmae = "ul" + (minId + 1);
	imgLoading++;
	document.getElementById(elemNmae).innerHTML
						+= ('<li class="pic-item" id="' + imgLoading + '">'
						+ '<a><img src=' + "/img/loading.jpg" + '></a>'
						+ '<div class="info"></div></li>');
}


function addCom(page){
	curPage = page;
	var i = 0;
	var comList = document.getElementById('repeat-list');
	comList.innerHTML 
			= ('<div class="comment-li">'
			+ '<h5 class="comment-user">'
			+ jsonCom[0].who[i]
			+ ': </h5>'
			+ '<p>' + jsonCom[0].content[i]
			+ '</p></div>');
	for (i++; i < jsonCom[0].who.length; i++){
		comList.innerHTML
			+= ('<div class="comment-li">'
			+ '<h5 class="comment-user">'
			+ jsonCom[0].who[i]
			+ ': </h5>'
			+ '<p>' + jsonCom[0].content[i]
			+ '</p></div>');
	}
	comList.innerHTML
			+= ('<div class="comment-li">'
			+ '<h5 class="comment-user">'
			+ "页数"
			+ ': </h5>'
			+ '<p>' + "第" + page + "页"
			+ '</p></div>');
}


window.onscroll = function (){
	var scrollT = document.documentElement.scrollTop || document.body.scrollTop;
	var scrollH = document.documentElement.scrollHeight || document.body.scrollHeight;
	var clientH = 400;
	if (scrollT >= scrollH - clientH - 500){
		for (var i = 0; i < 4; i++){
			addLoad();
			addOne();			
		}
	}
}


function showShade(id){
	src = jsonObj[id - 1].picSrc;
	document.getElementById('shade-pic').innerHTML 
					= ('<img src=' + src + ' id=' + id + ' >');
	$('#mask').css({
		'height': $(document).height(),
        'width' : $(document).width(),
        'display': 'block'
	}).show();
	$('#shade').css({
		'display': 'block'
	}).show();
	$('#shade-pic img').css({
		'height': Math.min(510, $('#shade-pic').innerHeight())
	}).show();
	$('#shade-comment').css({
		'height': $('#shade-pic').innerHeight()
	}).show();

	curId = id;
	curComs = 0;
	curPage = 1;
	loadComment(curId, curPage);
}


function getDistance(a, b, x, y){
	with(Math){
		var x1 = cos(a) * cos(b);
		var x2 = cos(x) * cos(y);
		var y1 = cos(b) * sin(a);
		var y2 = cos(y) * sin(x);
		var z1 = sin(b);
		var z2 = sin(y);
		var m = acos(x1 * x2 + y1 * y2 + z1 * z2);
		var n = a / 180 * PI * 6371;
		return n;
	}
}


$(function(){
	$("#close").click(function(){
		$("#shade").hide();
		$("#mask").hide();
		curId = 0;
		curPage = 1;
		curComs = 0;
	});
	$('#pre').click(function(){
		loadComment(curId, curPage - 1);
	});
	$('#nex').click(function(){
		loadComment(curId, curPage + 1);
	});
	$('#pre').mouseover(function(){
		$('#pre').css({
			"background-color": "#f0f0f0",
			"color" : "#808080"})
	});
	$('#nex').mouseover(function(){
		$('#nex').css({
			"background-color": "#c0c0c0",
			"color": "#808080"})
	});
	$('#pre').mouseout(function(){
		$('#pre').css({
			"background-color": "#282828",
			"color": "#a0a0a0"})
	});
	$('#nex').mouseout(function(){
		$('#nex').css({
			"background-color": "#282828",
			"color": "#a0a0a0"})
	});


	//初始加载10张图片
	for (var i = 0; i < 10; i++){
		addLoad();
	}
	loadData();

	//获取当前地理位置
	if (navigator.geolocation) {
        navigator.geolocation.getCurrentPosition(function(pos){
        	curLongi = pos.coords.longitude;
        	curLati  = pos.coords.latitude;
        })
    }
})

