/*
*index.js
*__author__ = 2013013316
*__email__  = wangbinbinsx@gmail.com
*/
var chatDB   = new Firebase('https://amber-inferno-9511.firebaseio.com/');
var userList = $('#user-list');			//用户列表
var msgList  = $('#msg-list');			//聊天信息
var userName = $('#nameInput');			//昵称输入框
var userMsg  = $('#messageInput');		//聊天信息输入框
var sendBtn  = $('#sendmsg');			//发送按钮
var quitBtn  = $('#quitNow');			//退出当前用户按钮
var allUsers = [];						//所有用户


function isInAry(ary, val){
	for (var i in ary){
		if (val == ary[i]){
			return true;
		}
	}
	return false;
}

/*
*输入昵称和聊天信息后的响应
*/
function respond(){
	var username = userName.val();
	if (username == ""){
		alert("请输入昵称！");
	}
	if (isInAry(allUsers, username) && userName.attr("disabled") != "disabled"){
		userName.val('');
		userMsg.val('');
		userName.attr("placeholder", "enter a name");
		userMsg.attr("placeholder", "send a message");
		alert("当前昵称已存在，请换一个！");
		return;
	}
	var message  = userMsg.val();
	if (message == ""){
		alert("话不能为空!");
	}

	chatDB.push({name: username, text: message});
	userMsg.val('');
	userName.attr("disabled", true);
	document.getElementById('head-user').innerHTML = $('#nameInput').val();
}

/*
*
*/
chatDB.on('child_removed', function(oldChildSnapshot){
	var SysMsg = oldChildSnapshot.val().name + "已经离线";
	removeUser(oldChildSnapshot.val().name);
	for (var i in allUsers){
		if (allUsers[i] == oldChildSnapshot.val().name){
			allUsers[i] = "";
		}
	}
	document.getElementById('head-user').innerHTML = "username";
	alert(SysMsg);
});


chatTime = new Firebase('https://amber-inferno-9511.firebaseio.com/time/');
chatTime.on('value', function(snapshot){
	var deltaTime = 12000;
	var set = snapshot.val();
	var username = set.name;
	var usertime = set.time;
	var timeNow   = (new Date()).getTime();
	if (!isInAry(allUsers, username) && Math.abs(timeNow - usertime) <= deltaTime){
		allUsers.push(username);
		adduserList(username);
	}
})

chatDB.on('child_added', function(snapshot){
	if (snapshot.key() == "time"){
		return;
	}
	var data = snapshot.val();
	var username = data.name;
	var usermsg  = data.text;
	if (username != "" && usermsg != ""){
		addmsgList(username, usermsg);
	}
});


sendBtn.click(respond);

quitBtn.click(function(){
	chatDB.child('time').remove();
	userName.val('');
	userName.attr("disabled", false);
	userName.attr("placeholder", "enter a name");
});


userMsg.keypress(function(e){
	if (e.keyCode == 13){
		respond();
	}
});

/*
*每隔1秒钟向服务器发送当前时间
*以说明用户在线
*/
function allsendMsg() {
	var date = (new Date()).getTime();
	if (userName.attr('disabled') == "disabled"){
		chatDB.child('time').set({name: userName.val(), time: date});
	}
	setTimeout(allsendMsg, 1000);
}
allsendMsg();

window.onunload = function(){
	chatDB.child('time').remove();
};

function adduserList(username){
	userList.append('<li id="' + username + '"><strong>' + username + '</strong></li>');
}

function addmsgList(name, msg){
	msgList.append('<li><div class="one"><div class="user"><span>' 
	+ name + '</span></div><div class="msg"><p>' + msg + '</p></div></div></li>');
	$('#chat-content').scrollTop( $('#chat-content')[0].scrollHeight );
}

function removeUser(username){
	document.getElementById(username).remove();
}