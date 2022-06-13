<!doctype html>
<html lang="pl">
<head>
  <meta charset="utf-8"><link href="https://fonts.googleapis.com/css?family=Lato" rel="stylesheet">
  <title>Ułóż plan</title>
  <link rel="shortcut icon" type="image/x-icon" href="favicon.ico"/>
  	<style>
	
	body{
	font-family: Lato, "Segoe UI";	
	margin: 1px;	
	}
	.schedulebox{
	height: 80px;
	width: 363px;

	margin-bottom: 10px;
	}
	
	h4{margin-top: 0;}
	
	a{
	text-decoration: none;
	color: #002;
	font-weight: bold;
	}
	a:hover{
	text-decoration: underline;
	color: #002;
	font-weight: bold;
	}
	
	.time{
	float: left;
	width: 45px;
	height: 80px;
	padding-right: 5px;
	text-align: right;
	background-color: #ffd884;
	border-radius: 5px 5px 0 0;
	border-radius: 10px 0 0 10px;
	/*border: 1px solid black;*/
	}
	
	.infobox{
	float: right; 
	height: 80px;
	width: 313px;
	background-color: #ffcd63;
	position:relative;
	border-radius: 0 10px 10px 0;
	/*border: 1px solid black;*/
	}
	
	.name{
	z-index: 1;
	position: absolute; 
	width: 310px;
	text-align: center;
	margin: 3px;
	}
	
	.belowname{
	height: 20px;
	padding-top: 60px;
	}
	
	.teacherroom{
	font-size: 11px;
	float:left; 
	clear: both;
	margin-left: 2px;
	}
	
	.typegroup{
	font-size: 11px;
	margin-right: auto;
	float: right;
	cursor: pointer;
	margin-right: 3px;
	}
	table
	{
	border-collapse: collapse;
	margin-left: auto;
	margin-right: auto;
	text-align:left;
	}
	td,tr{
	border-top: 1px solid #000;	
	}
	tr{
	background-color: #dfefff;
	}
	tr:hover{
	background-color: #ffff99;
	}
	#choicehead
	{
		padding-top: 40px;
		text-align: center;
		clear: both;
		background-color: #dfefff;
	}
	.day{
		float: left;
		text-align: center;
		width: 376px; 
		
	}

	.box{
		width:32px;
		height: 32px;
	}
	
	.underdays
	{
		background-color: #dfefff;
	}
	
	h1{
		font-size: 55px;
	}
	.entry{
		background-color: #dfefff;
		height: 120px;
		vertical-align: middle;
		line-height: 30px;
	}
	</style>
	
<script>
	
</script>
	
</head>
<body style="background-color: #ffe4aa; text-align: center;">
<!--<div class="controls">
	<form  onsubmit="return false">
		<input type="text" type="number" maxlength="6"  placeholder="Numer indeksu"> 
		<input type="submit" value="Zapisz" onclick="save()">
		<input type="submit" value="Wczytaj" onclick="read()">
		<input type="submit" value="Wyczyść" onclick="clear()">
	</form>

</div>-->
<div class="entry"><h1>STRONA NIE DZIAŁA, ZADZIAŁA JAK ADMIN SIĘ ODKOPIE SPOD STOSU EGZAMINÓW</h1><br /><h4>Witaj na stronie pomagającej w ułożeniu planu zajęć w IM UWr. <br />Dane pochodzą z USOS-a. <br /> <i>Autor: Dawid Migacz.&nbsp;&nbsp;</i> Ostatnia aktualizacja danych: 
<?php
	//0,577 215 664 901 532 860 606 512 090 082 402 431 042 159 335 939 923 598
	
	$line = date('Y-m-d H:i:s') . " - $_SERVER[REMOTE_ADDR]";
	file_put_contents('visitors.log', $line . PHP_EOL, FILE_APPEND);
	
	error_reporting(-1);
	//$data = file_get_contents('http://www.math.uni.wroc.pl/studia/plany_zajec/planL.php');
	$data = file_get_contents('planL.php');
	//phpinfo(); 
	//echo $data;
	//if($data === FALSE){echo "<script type='text/javascript'>alert('Błąd ładowania danych ze strony Instytutu. Odśwież stronę.');</script>";}
	echo substr($data,stripos($data, "Data ostatniej aktualizacji danych")+36,16).".<br />\n";
	//echo stripos($data, "Data ostatniej aktualizacji danych");
	$data = str_replace("</td><td","</td>\t<td",$data);
	$data = str_replace("</tr><tr>","</tr>\n<tr>",$data);
	$data = strip_tags($data,"<a>");
	$data = str_replace("&nbsp;","",$data);
	$data = str_replace(" — ","\t",$data);
	$data = str_replace("(2019) Przedmioty obowiązkowe (O)\n","",$data);
	$data = str_replace("(2019) Standardowe przedmioty do wyboru (L)\n","",$data);
	$data = str_replace("(2019) Zaawansowane przedmioty do wyboru (M)\n","",$data);
	$data = str_replace("(2019) Zaawansowane przedmioty do wyboru (M)(2019) E-learning (E)\n","",$data);
	$data = str_replace("(2019) Zaawansowane przedmioty do wyboru (M)(2019) Seminaria przeglądowe (S)\n","",$data);
	$data = str_replace("(2019) Przedmioty z zakresu nauk humanistycznych i społecznych (H)\n","",$data);
	$data = str_replace("(2019) Przedmioty dla spec. nauczycielskiej (N)\n","",$data);
	$data = str_replace("(2019) Przedmioty z zakresu nauk przyrodniczych (NP)\n","",$data);
	$data = str_replace("Pozostałe przedmioty\n","",$data);
	$data = str_replace('<a ','!<a ',$data);
		//$data = str_replace("\t",", ",$data);
	$data = preg_replace('/^[ \t]*[\r\n]+/m', '', $data);
	$data = substr_replace($data,"",0,stripos($data, "uwagi")+7);
	$data = preg_replace('/^[ \t]*[\r\n]+/m', '', $data);
	$lines = explode("\n",$data);
	$course="";
	array_pop($lines);
	foreach($lines as &$row)
	{
		if(substr($row,0,1)=="!") 
		{
			$course=substr($row,1);
			$row="";
		}
		else
		{
			$row=$course."\t".$row;
		}
	}
	$data=implode("\n",$lines);
	$data = preg_replace('/^[ \t]*[\r\n]+/m', '', $data);
	$lines = explode("\n",$data);
	foreach($lines as $index => &$row)
	{
		$cells[$index] = explode("\t",$lines[$index]);
		if(strlen($cells[$index][5])>3) {if($cells[$index][5][3]==='0') $cells[$index][5]=$cells[$index][5].'0';}
		if(strlen($cells[$index][6])>3) {if($cells[$index][6][3]==='0') $cells[$index][6]=$cells[$index][6].'0';}
	}
	
/*
$fp = fopen('lidn.txt', 'w');
fwrite($fp, json_encode($cells));
fclose($fp);
*/
	//echo nl2br($data);
	//echo "---------------------";
	//$sfile = fopen("courses.txt", "w");
	//echo "<br /><br />\n\n\n\n\n";
	//echo json_encode($cells);
	//echo "<br /><br />\n\n\n\n\n";
	//print_r($cells);
	echo "<script type='text/javascript'>\n";
	echo "var cells = ".json_encode($cells) . ";\n";
	echo "var lines = ".count($cells) . ";\n";
	echo "</script>";
?>
Aby usunąć przedmiot z planu, odznacz checkbox lub kliknij na typ zajęć.</h4></div><h1>PLAN ZAJĘĆ</h1><div class="day"><div id="p">
<h2>PONIEDZIAŁEK</h2>
</div></div>
<div class="day"><div id="w">
<h2>WTOREK</h2>
</div></div>
<div class="day"><div id="s">
<h2>ŚRODA</h2>
</div></div>
<div class="day"><div id="c">
<h2>CZWARTEK</h2>
</div></div>
<div class="day"><div id="f">
<h2>PIĄTEK</h2>
</div></div>
<script type='text/javascript'> 
var hours = ["8.15","8.30","8.45","9.00","9.15","9.30","9.45","10.00","10.15","10.30","10.45","11.00","11.15","11.30","11.45","12.00","12.15","12.30","12.45","13.00","13.15","13.30","13.45","14.00","14.15","14.30","14.45","15.00","15.15","15.30","15.45","16.00","16.15","16.30","16.45","17.00","17.15","17.30","17.45","18.00","18.15","18.30","18.45"]
	function divClicked(nr)
	{
		var checkBox = document.getElementById("chk"+nr);
		var text = document.getElementById("txt"+nr);
		text.style.display = "none";
		checkBox.checked = false;
	};

for(var x=0; x<44;x++)
for(var i=0; i<lines;i++)
	{
		var el=document.getElementById('p')
		if(cells[i][5].length>2 && cells[i][4] == "poniedziałek" && cells[i][5]==hours[x])
		{
			var text = "";
			text += '<div style="display:none" class="schedulebox" id="txt'+i+'"><div class="time">';
			text +=	cells[i][5] + "<br /><br /><br />" + cells[i][6];
			text += '</div><div class="infobox"  title="'+cells[i][8]+cells[i][9]+'">';
			text += '<div class="name">' + cells[i][0];
			text += '</div><div class="belowname"><div class="teacherroom">'+ cells[i][3];
			if(cells[i][7].length>0) text +=' (s. '+cells[i][7]+')';
			text += '</div><div class="typegroup" onclick="divClicked('+i+')">' + cells[i][2];
			if(cells[i][1].length>0) text +=' (gr. '+cells[i][1]+')';
			text +=' </div></div></div></div>';
			el.innerHTML += text;
		}
	}
	
for(var x=0; x<44;x++)
for(var i=0; i<lines;i++)
	{
		var el=document.getElementById('w')
		if(cells[i][5].length>2 && cells[i][4] == "wtorek" && cells[i][5]==hours[x])
		{
			var text = "";
			text += '<div style="display:none" class="schedulebox" id="txt'+i+'"><div class="time">';
			text +=	cells[i][5] + "<br /><br /><br />" + cells[i][6];
			text += '</div><div class="infobox"  title="'+cells[i][8]+cells[i][9]+'">';
			text += '<div class="name">' + cells[i][0];
			text += '</div><div class="belowname"><div class="teacherroom">'+ cells[i][3];
			if(cells[i][7].length>0) text +=' (s. '+cells[i][7]+')';
			text += '</div><div class="typegroup" onclick="divClicked('+i+')">' + cells[i][2];
			if(cells[i][1].length>0) text +=' (gr. '+cells[i][1]+')';
			text +=' </div></div></div></div>';
			el.innerHTML += text;
		}
	}
	
	
for(var x=0; x<44;x++)
for(var i=0; i<lines;i++)
	{
		var el=document.getElementById('s')
		if(cells[i][5].length>2 && cells[i][4] == "środa" && cells[i][5]==hours[x])
		{
			var text = "";
			text += '<div style="display:none" class="schedulebox" id="txt'+i+'"><div class="time">';
			text +=	cells[i][5] + "<br /><br /><br />" + cells[i][6];
			text += '</div><div class="infobox"  title="'+cells[i][8]+cells[i][9]+'">';
			text += '<div class="name">' + cells[i][0];
			text += '</div><div class="belowname"><div class="teacherroom">'+ cells[i][3];
			if(cells[i][7].length>0) text +=' (s. '+cells[i][7]+')';
			text += '</div><div class="typegroup" onclick="divClicked('+i+')">' + cells[i][2];
			if(cells[i][1].length>0) text +=' (gr. '+cells[i][1]+')';
			text +=' </div></div></div></div>';
			el.innerHTML += text;
		}
	}
	
for(var x=0; x<44;x++)
for(var i=0; i<lines;i++)
	{
		var el=document.getElementById('c')
		if(cells[i][5].length>2 && cells[i][4] == "czwartek" && cells[i][5]==hours[x])
		{
			var text = "";
			text += '<div style="display:none" class="schedulebox" id="txt'+i+'"><div class="time">';
			text +=	cells[i][5] + "<br /><br /><br />" + cells[i][6];
			text += '</div><div class="infobox"  title="'+cells[i][8]+cells[i][9]+'">';
			text += '<div class="name">' + cells[i][0];
			text += '</div><div class="belowname"><div class="teacherroom">'+ cells[i][3];
			if(cells[i][7].length>0) text +=' (s. '+cells[i][7]+')';
			text += '</div><div class="typegroup" onclick="divClicked('+i+')">' + cells[i][2];
			if(cells[i][1].length>0) text +=' (gr. '+cells[i][1]+')';
			text +=' </div></div></div></div>';
			el.innerHTML += text;
		}
	}
	
for(var x=0; x<44;x++)
for(var i=0; i<lines;i++)
	{
		var el=document.getElementById('f')
		if(cells[i][5].length>2 && cells[i][4] == "piątek" && cells[i][5]==hours[x])
		{
			var text = "";
			text += '<div style="display:none" class="schedulebox" id="txt'+i+'"><div class="time">';
			text +=	cells[i][5] + "<br /><br /><br />" + cells[i][6];
			text += '</div><div class="infobox"  title="'+cells[i][8]+cells[i][9]+'">';
			text += '<div class="name">' + cells[i][0];
			text += '</div><div class="belowname"><div class="teacherroom">'+ cells[i][3];
			if(cells[i][7].length>0) text +=' (s. '+cells[i][7]+')';
			text += '</div><div class="typegroup" onclick="divClicked('+i+')">' + cells[i][2];
			if(cells[i][1].length>0) text +=' (gr. '+cells[i][1]+')';
			text +=' </div></div></div></div>';
			el.innerHTML += text;
		}
	}
</script>




<div id="holder"></div>
<div id="choicehead"><h2>Wybierz przedmioty do umieszczenia w planie:<br /></h2>
<table id="tab" cellpadding="6"></table></div>
<script type='text/javascript'> 
	function myFunction(nr) {
		var checkBox = document.getElementById("chk"+nr);
		var text = document.getElementById("txt"+nr);
		if (checkBox.checked == true){
		text.style.display = "block";
		} else {
		text.style.display = "none";
	}
};
	
	
	var el = document.getElementById('holder');
	var table = document.getElementById("tab");
	for(var i=0; i<lines;i++)
	{
		if(cells[i][5].length>2)
		{
			var row = table.insertRow(-1);
			var cell0 = row.insertCell(0);
			var cell1 = row.insertCell(1);
			var cell2 = row.insertCell(2);
			var cell3 = row.insertCell(3);
			var cell4 = row.insertCell(4);
			var cell5 = row.insertCell(5);
			var cell6 = row.insertCell(6);
			var cell7 = row.insertCell(7);
			cell0.innerHTML='<label class="check" onclick="myFunction('+i+')><div class="box" ><input type="checkbox" id="chk'+i+'" onclick="myFunction('+i+')"></div></label>';
			cell1.innerHTML=cells[i][0]+" "; //przedmiot
			cell2.innerHTML=cells[i][2]+" "; //typ
			if(cells[i][1].length>0){cell3.innerHTML='gr. '+cells[i][1];+"&nbsp;&#32;&nbsp;&#32;&nbsp;"} //grupa
			cell4.innerHTML=cells[i][3]+" &nbsp;&#32;"; //prow
			cell5.innerHTML=cells[i][4]+" &#32;&nbsp;"; //dzien
			cell6.innerHTML=cells[i][5]+" – "+cells[i][6]; //czas
			if(cells[i][7].length>0) {cell7.innerHTML='s. '+cells[i][7]+" ";}

		}
	}
	
	var ff = 1;
	
</script>











</body>
</html>






























