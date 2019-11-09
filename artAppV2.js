
var operation;  // operation
var editid;
var email;
var pass;

$(document).ready(function () {
    $('.editdata').hide();
    $("#search-btn").click(getMatches);
    operation = "Find Last";
    $("#clear").click(clearResults);
    $("#createAcct").click(function()
	{
	    $("#Home").hide();
	    $("#myModal").modal('hide');
	    $("#CreateAccountPage").show();
         });

   $("#createAcctButton").click(function()
	{
	   	email= $('#inputEmailCreate').val();
	        pass = $('#inputPWCreate').val();
	        type = "Create";
	   	//console.log("yo we in here");
        	$.ajax({
		url: '/cgi-bin/guidotti1_createUserAccounts.cgi?email='+email+'&password='+pass+'&type='+type,
		dataType: 'text',
		success: processUserCreate,
		error: function(){alert("Error: Something went wrong");}
    		});
   	});
   $("#UserLogInBtn").click(function()
	{
		email= $('#inputEmailLogin').val();
	        pass = $('#inputPWLogin').val();
	        type = "Login";
	        console.log("UserLogInBtn");
		$.ajax({
		url: '/cgi-bin/guidotti1_createUserAccounts.cgi?email='+email+'&password='+pass+'&type='+type,
		dataType: 'text',
		success: processUserLogin,
		error: function(){alert("Error: Something went wrong");}
    		});
	   });
	   
	   
	    
	    

    $(".dropdown-menu a").click(function(){
	console.log("pick!"+$(this).text());
	if ( $(this).hasClass("main-menu") ) {
	    $(this).parents(".dropdown").find('.selection').text($(this).text());
	    operation=$(this).text();
	    console.log("Main-menu");
	    changeOperation(operation);	    
	} else if ($(this).hasClass("add-item")) {
	    $(this).parents(".dropdown").find('.selection').text($(this).text());
	    console.log($(this).text());
	} else if ($(this).hasClass("edit-item")) {
	    $(this).parents(".dropdown").find('.selection').text($(this).text());
	    console.log($(this).text());
	} 	
    });
});

changeOperation(operation);

function changeOperation(operation){
    if(operation=="Add Entry"){
	console.log("Add Entry");
	$('#addmessage').empty();
	$('.inputdata').show();
	$('.searchbox').hide();
	$('.results').hide();
	$('.editdata').hide();}
    else{
	console.log("not add entry");
	$('.editdata').hide();
	$('.inputdata').hide();
	$('.results').show();
	$('.searchbox').show();
    }    
}


function processUserCreate(results)
{
	console.log("made it to proccesUser");
	console.log("Results:"+results);
	var a = results.split(" ");
	if (a.length == 1)
	{
		$("#Home").show();
		$("#CreateAccountPage").hide();
		//appendNav = "<p> Logged in as : ";
		document.getElementById("LogInInfo").innerHTML = "Logged in as : "+email;
		var appendNavButton = "<button type='button' class='btn btn-primary' id = 'LogOutBtn' >Log out!</button>";
		var $appendNavButton = $(appendNavButton).bind("click", function()
		{
		userLogOut();
		});
		$('#HomeNav').append($appendNavButton);
		$('#LogInBtn').hide();
	}
	else
	{
		appendH = "<h1 class='display-3'>";
		appendH += results;
		appendH += "</h1>";
		$('#createAcctResults').append(appendH);
	}
}

function processUserLogin(results)
{
	var a = results.split(" ");
	if (a.length == 1)
	{
		console.log("processUserLogin a.length == 1 (success)");
		//$("#Home").show();
		//$("#CreateAccountPage").hide();
		document.getElementById("LogInInfo").innerHTML = "Logged in as : "+email;
		var appendNavButton = "<button type='button' class='btn btn-primary' id = 'LogOutBtn' >Log out!</button>";
		var $appendNavButton = $(appendNavButton).bind("click", function()
		{
		userLogOut();
		});
		$('#HomeNav').append($appendNavButton);
		$('#LogInBtn').hide();
		$("#myModal").modal('hide');
	}
	else 
	{
		console.log("processUserLogin (failure)");
		appendH = "<h1 class='display-3'>";
		appendH += results;
		appendH += "</h1>";
		$('#loginresults').append(appendH);
	}
}

function userLogOut()
{
	email = "";
	document.getElementById("LogInInfo").innerHTML = "";
	$('#LogOutBtn').hide();
	$('#LogInBtn').show();
}

// Build output table from ^ delimited list
function buildTable(list) {
    var a = list.split("^");
    if (a.length < 1) {
	return "<h3>Internal Error</h3>";
    } else if (a.length == 1) {
	return "<h3>Nothing Found</h3>";
    } else {
	var result = '<table class="w3-table-all w3-hoverable" border="2"><tr><th>Last</th><th>First</th><th>Born-Died</th><th>Title</th><th>Date</th><th>Technique</th><th>Location</th><th>URL</th><th>Form</th><th>Type</th><th>School</th><th>Timeframe</th><th>View Art</th><tr>';
	var aLen = a.length;
	for (var i = 0; i < aLen-1; i+=13) {
	    result += "<tr><td class='Last'>"+a[i]+"</td><td class='First'>"+a[i+1]+"</td><td class='Born-Died'>"+a[i+2]+"</td><td class='Title'>"+a[i+3]+"</td>";
	    result += "<td class='Date'>"+a[i+4]+"</td><td class='Technique'>"+a[i+5]+"</td><td class='Location'>"+a[i+6]+"</td><td class='Url'>"+a[i+7]+"</td>";
	    result += "<td class='Form'>"+a[i+8]+"</td><td class='Type'>"+a[i+9]+"</td><td class='School'>"+a[i+10]+"</td><td class='Timeframe'>"+a[i+11]+"</td>";
	    result += "<td><button type = 'button' ID ='"+a[i+12]+"' class = 'btn btn-primary btn-sm view'>View Art</button></td></tr>";
	}
	result += "</table>";
	
	return result;
    }
}


function processResults(results) {
    console.log("Results:"+results);
    $('#searchresults').empty();
    $('#searchresults').append(buildTable(results));
    $(".view").click(viewArt);
}

function viewArt(){
	$("#Home").hide();
	$("#ViewArtPage").show();
	console.log("WE VIEWING ART BOYS");
	var row = $(this).parents("tr");
	//console.log("Title on the record : "+ $(row).find('.Title').text());
	Title = $(row).find('.Title').text();
	Last = $(row).find('.Last').text();
	First = $(row).find('.First').text();
	URL = $(row).find('.Url').text();
	//console.log("URL on the record : "+ URLS);
	appendFigure = "<figure class='figure'>";
        appendFigure += "<img src='"+URL+"' class='img-fluid' alt='Responsive image'>";
        appendFigure += "<figcaption class='figure-caption text-right'>'"+Title+"'</figcaption>";
	appendFigure += "<figcaption class='figure-caption text-right'> by  "+First+" "+Last+" </figcaption>";
        appendFigure += "</figure>";
	commentBox = "<div class='container pb-cmnt-container' id = 'commentArea'>";
        commentBox += "<div class='panel panel-info'>";
	commentBox +=  "<div class='panel-body'>";
	commentBox +=  "<textarea placeholder='Write your comment here!' class='pb-cmnt-textarea'></textarea>";
	commentBox += "</div>";
	commentBox += "</div>";
	commentBox += "</div>";
	commentButton =  "<button class='btn btn-primary pull-right' type='button' id = 'SubmitCommentBtn' >Submit Comment</button>";
	$commentButton = $(commentButton).bind("click", function()
		{
		userComment();
		});
	
	var id = $(row).find('.btn btn-primary btn-sm view').id;
	console.log("ID HERE IS : "+id);
		
	$('#ViewArtResults').append(appendFigure);
	$('#ViewArtResults').append(commentBox);
        $('#commentArea').append($commentButton);
}

function userComment(){
    console.log("USER COMMENTING");
}

function clearResults() {
    $('#searchresults').empty();
}

function getMatches(){
    $('.editdata').hide();
    $('#searchresults').empty();
    $.ajax({
	url: '/cgi-bin/guidotti1_artApp.cgi?find='+$('#search').val()+'&operation='+operation,
	dataType: 'text',
	success: processResults,
	error: function(){alert("Error: Something went wrong");}
    });
}

    
