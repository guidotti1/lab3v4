
var operation;  // operation
var editid;
var email;
var pass;
var artid;
var vote;

$(document).ready(function () {
    $('.editdata').hide();
    $("#search-btn").click(getMatches);
    operation = "Find Last";
    $("#clear").click(clearResults);
    $("#LogOutBtnView").hide();
    $("#LogOutBtnHome").hide();
    $("#LogOutProfilePage").hide();
    $("#LogOutBtnView").click(function()
	{
	    userLogOut();
        });
    $("#LogOutBtnHome").click(function()
	{
	    userLogOut();
        });
	
    $("#LogOutProfilePage").click(function()
        {
	    userLogOut();
   	});
	    
	    
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
    $("#ReturnHomeBtn").click(function()
	{
		$("#ViewArtPage").hide();
		$("#Home").show();
	});

    $("#ReturnHomeBtnProfile").click(function()
	{
	        $("#UserProfilePage").hide();
		$("#Home").show();
	});
    
    $("#ViewUserProfile").click(function()
	{

	        if (email == "" || typeof email === "undefined")
    		{
	    	alert("You must be logged in to view your profile!");
   		 }
   		else
   		{
		$("#Home").hide();
	     	$("#UserProfilePage").show();
		$.ajax({
			url: '/cgi-bin/guidotti1_viewUserProfile.cgi?email='+email,
			dataType: 'text',
			success: viewProfile,
			error: function(){alert("Error: Something went wrong");}
    			});
   		}	   
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

function viewProfile(results)
{
	$("#UsersComments").empty();
	$("#UsersLikes").empty();
	console.log("Results for viewProfile"+results);
	var  a = results.split("®"); //break up username we are looking at, comments and votes
	var currentUsername = a[0]
	document.getElementById("PutUsernameHere").innerHTML = "Viewing the profile of : "+currentUsername;
	var commentsString = a[1];
	console.log("a[0] :"+a[0]);
	console.log("a[1] :"+a[1]);
	console.log("a[2] :"+a[1]);
	var commentsSeparated = commentsString.split("‰"); //break up comments by painting 
	//handles all comments for the user
	for (var i = 0; i < commentsSeparated.length - 1; i++)
	{
		var artComments = commentsSeparated[i].split("^");
		var artistLastname = artComments[1];
		var artistFirstname = artComments[2];
		var artURL = artComments[3];
		var artTitle = artComments[4];
		appendFigure = "<figure class='figure'>";
		appendFigure += "<img src='"+artURL+"' class='img-fluid' alt='Responsive image'>";
        	appendFigure += "<figcaption class='figure-caption text-right'>'"+artTitle+"'</figcaption>";
		appendFigure += "<figcaption class='figure-caption text-right'> by  "+artistFirstname+" "+artistLastname+" </figcaption>";
        	appendFigure += "</figure>";
		$("#UsersComments").append(appendFigure);
		$('#UsersComments').append("<h4> Comments for this piece of art <\h4>");
		$('#UsersComments').append("<div class='media'>");
		
		for (var j = 5; j < artComments.length; j++)
		{	
			appendDiv = "<div class='media-body'>";
			appendDiv += artComments[j];
			appendDiv += "</div>";
			$('#UsersComments').append(appendDiv);
		}	
		$('#UsersComments').append("</div>");	
	}
	
	//handles all votes (upvotes and downvotes) for the user
	var votesString = a[2];
	var votesTypeSeparated = votesString.split("µ");
	var upvotes = votesTypeSeparated[0];
	var u = upvotes.split("^");
	for (var i = 1; i < u.length-1; i+=4)
	{
		var artistLastname = u[i];
		var artistFirstname = u[i+1];
		var artURL = u[i+2];
		var artTitle = u[i+3];
		console.log("lastname: "+artistLastname);
		console.log("firstname: "+artistFirstname);
		console.log("url: "+artURL);
		console.log("title: "+artTitle);
		appendFigure = "<figure class='figure'>";
		appendFigure += "<img src='"+artURL+"' class='img-fluid' alt='Responsive image'>";
        	appendFigure += "<figcaption class='figure-caption text-right'>'"+artTitle+"'</figcaption>";
		appendFigure += "<figcaption class='figure-caption text-right'> by  "+artistFirstname+" "+artistLastname+" </figcaption>";
        	appendFigure += "</figure>";
		$("#UsersLikes").append(appendFigure);
	}
		
	var downvotes = votesTypeSeparated[1];
	var d = downvotes.split("^");
	for (var i = 1; i < d.length-1; i+=4)
	{
		var artistLastname = d[i];
		var artistFirstname = d[i+1];
		var artURL = d[i+2];
		var artTitle = d[i+3];
		appendFigure = "<figure class='figure'>";
		appendFigure += "<img src='"+artURL+"' class='img-fluid' alt='Responsive image'>";
        	appendFigure += "<figcaption class='figure-caption text-right'>'"+artTitle+"'</figcaption>";
		appendFigure += "<figcaption class='figure-caption text-right'> by  "+artistFirstname+" "+artistLastname+" </figcaption>";
        	appendFigure += "</figure>";
		$("#UsersDislikes").append(appendFigure);
	}
}

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
		document.getElementById("LogInInfo").innerHTML = "Logged in as : "+email;
		document.getElementById("LogInInfoViewArt").innerHTML = "Logged in as : "+email;
		document.getElementById("LogInInfoProfilePage").innerHTML = "Logged in as : "+email;
		$('#LogInBtn').hide();
		$('#LogInBtnViewArt').hide();
		$("#LogInBtnProfilePage").hide();
	        $("#LogOutBtnView").show();
                $("#LogOutBtnHome").show();
		$("#LogOutProfilePage").show();
	}
	else
	{
		$('#createAcctResults').empty();
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
		document.getElementById("LogInInfo").innerHTML = "Logged in as : "+email;
		document.getElementById("LogInInfoViewArt").innerHTML = "Logged in as : "+email;
		document.getElementById("LogInInfoProfilePage").innerHTML = "Logged in as : "+email;
		$('#LogInBtn').hide();
		$('#LogInBtnViewArt').hide();
		$("#LogInBtnProfilePage").hide();
	        $("#LogOutBtnView").show();
                $("#LogOutBtnHome").show();
		$("#LogOutProfilePage").show();
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
	document.getElementById("LogInInfoViewArt").innerHTML = "";
	document.getElementById("LogInInfoProfilePage").innerHTML = "";
	$('#LogOutBtnHome').hide();
	$('#LogOutBtnView').hide();
	$("#LogOutProfilePage").hide();
	$('#LogInBtn').show();
	$('#LogInBtnViewArt').show();
	$("#LogInBtnProfilePage").show();
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
	$('#ViewArtResults').empty();
	$("#Home").hide();
	$("#ViewArtPage").show();
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
	//commentBox = "<div class = 'row'>";
	//commentBox += "<div class = 'col-sm-6'>";
	commentBox = "<div class='container pb-cmnt-container' id = 'commentArea'>";
        commentBox += "<div class='panel panel-info'>";
	commentBox +=  "<div class='panel-body'>";
	commentBox +=  "<textarea placeholder='Write your comment here!' class='pb-cmnt-textarea' id = 'CommentBox'></textarea>";
	commentBox += "</div>";
	commentBox += "</div>";
	commentBox += "</div>";
	commentButton =  "<button class='btn btn-primary pull-right' type='button' id = 'SubmitCommentBtn' >Submit Comment</button>";
	$commentButton = $(commentButton).bind("click", function()
		{
		userComment();
		});
	upvoteButton = "<button class='btn btn-primary btn-sm' id = 'Upvote'><span class='glyphicon glyphicon-arrow-up'></span> Upvote</button>";
	downvoteButton = "<button class='btn btn-danger btn-sm' id = 'Downvote'><span class='glyphicon glyphicon-arrow-down'></span> Downvote </button>";
	$upvoteButton = $(upvoteButton).bind("click", function()
		{
		vote = "Upvote";
		userVote();
		
		});
	$downvoteButton = $(downvoteButton).bind("click", function()
		{
		vote = "Downvote";
		userVote();
		});
	artid = $(this).attr('ID');
	console.log("ID HERE IS : "+artid);
	$('#ViewArtResults').append(appendFigure);
	$('#ViewArtResults').append(commentBox);
        $('#commentArea').append($commentButton);
	$('#ViewArtResults').append($upvoteButton);
	$('#ViewArtResults').append($downvoteButton);
	displayComments();
}

function userVote()
{
  	console.log("USER VOTING ON ART");
	console.log("Vote : "+vote);
        if (email == "" || typeof email === "undefined")
   	{
	    alert("You must be logged in to vote on art!");
   	}
	
	   else
   	{
		type = "vote";
		$.ajax({
		url: '/cgi-bin/guidotti1_userVote.cgi?voteType='+vote+'&email='+email+'&ArtID='+artid+'&type='+type,
		dataType: 'text',
		success: proccessUserVote,
		error: function(){alert("Error: Something went wrong");}
    		});
   	}	
}

function proccessUserVote(results)
{
	console.log("In process user vote");
	console.log("Results:"+results);
	var a = results.split(" ");
	if (a.length == 1)
	{
		displayComments();
	}
	else 
	{
		alert("You have already voted on that piece of art");
	}
}

function displayVotes()
{
  type = "display";
  $.ajax({
	url: '/cgi-bin/guidotti1_userVote.cgi?voteType='+vote+'&email='+email+'&ArtID='+artid+'&type='+type,
	dataType: 'text',
	success: viewVotes,
	error: function(){alert("Error: Something went wrong");}
   });
}

function viewVotes(results)
{
	var a = results.split("^");
	var aLen = a.length;
	appendH3= "<h3 class='text-center'>User votes</h3>";
	appendH5 = "<h5 class ='text-center'>Total upvotes : "+a[1]+" Total downvotes : "+a[2]+"</h5";
	$('#Comments').append(appendH3);
	$('#Comments').append(appendH5);
}

function userComment(){
    console.log("USER COMMENTING");
    comment = $('#CommentBox').val();
    console.log("ARTID HERE IS : "+artid);
    console.log("Comment HERE IS : "+comment);
    console.log("Email HERE IS : "+email);
    type = "add";
    if (email == "" || typeof email === "undefined")
    {
	    alert("You must be logged in to comment!");
    }
   else
   {
		$.ajax({
		url: '/cgi-bin/guidotti1_userComment.cgi?comment='+comment+'&email='+email+'&artid='+artid+'&type='+type,
		dataType: 'text',
		success: displayComments,
		error: function(){alert("Error: Something went wrong");}
    		});
   }	   
}

function displayComments()
{
  $('#Comments').empty();
  type = "display";
  comment = "";
  $.ajax({
	url: '/cgi-bin/guidotti1_userComment.cgi?comment='+comment+'&email='+email+'&artid='+artid+'&type='+type,
	dataType: 'text',
	success: viewComments,
	error: function(){alert("Error: Something went wrong");}
   });
}

function viewComments(results) 
{
	console.log("Results are :"+results);
	var a = results.split("^");
	var aLen = a.length;
	appendH3= "<h3 class='text-center'>Comments</h3>";
	$('#Comments').append(appendH3);
	for (var i = 1; i < aLen; i+=2) {
		appendDiv = "<div class='media'>";
		appendDiv += "<div class='media-body'>";
		appendDiv += "<h5 class='mt-0'> Commenter: "+a[i+1]+"</h5>"
		appendDiv += a[i];
		appendDiv += "</div>";
		appendDiv += "</div>";
		$appendDiv = $(appendDiv).bind("click", function()
		{
		var username = $('.mt-0').html();
		console.log("username: "+username);
		$.ajax({
			url: '/cgi-bin/guidotti1_viewUserProfile.cgi?email='+username,
			dataType: 'text',
			success: viewProfile,
			error: function(){alert("Error: Something went wrong");}
    			});
		});
		$('#Comments').append($appendDiv);
	}
	displayVotes();	
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

    
