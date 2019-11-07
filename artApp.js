// JavaScript for Phone Application Demo Program
// Jim Skon, Kenyon College, 2017
var operation;  // operation
var editid;

$(document).ready(function () {
    $('.editdata').hide();
    $("#search-btn").click(getMatches);
    operation = "Find Last";
    $("#clear").click(clearResults);
    $("#createAcct").click(function()
	{
	    $('.page').hide();
	    $('#'+$(this).attr('data-page')).show();
         }
	    
	    

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

// Build output table from comma delimited list
function buildTable(list) {
    var a = list.split("^");
    if (a.length < 1) {
	return "<h3>Internal Error</h3>";
    } else if (a.length == 1) {
	return "<h3>Nothing Found</h3>";
    } else {
	var result = '<table class="w3-table-all w3-hoverable" border="2"><tr><th>Last</th><th>First</th><th>Born-Died</th><th>Title</th><th>Date</th><th>Technique</th><th>Location</th><th>URL</th><th>Form</th><th>Type</th><th>School</th><th>Timeframe</th><tr>';
	var aLen = a.length;
	for (var i = 0; i < aLen-1; i+=12) {
	    result += "<tr><td class='Last'>"+a[i]+"</td><td class='First'>"+a[i+1]+"</td><td class='Born-Died'>"+a[i+2]+"</td><td class='Title'>"+a[i+3]+"</td>";
	    result += "<td class='Date'>"+a[i+4]+"</td><td class='Technique'>"+a[i+5]+"</td><td class='Location'>"+a[i+6]+"</td><td class='Url'>"+a[i+7]+"</td>";
	    result += "<td class='Form'>"+a[i+8]+"</td><td class='Type'>"+a[i+9]+"</td><td class='School'>"+a[i+10]+"</td><td class='Timeframe'>"+a[i+11]+"</td></tr>";
	}
	result += "</table>";
	
	return result;
    }
}


function processResults(results) {
    console.log("Results:"+results);
    $('#searchresults').empty();
    $('#searchresults').append(buildTable(results));
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

    
