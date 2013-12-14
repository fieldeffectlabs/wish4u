<!DOCTYPE HTML>
<!--
	Astral 1.0 by HTML5 Up!
	html5up.net | @n33co
	Free for personal and commercial use under the CCA 3.0 license (html5up.net/license)
-->
<html>
	<head>
		<title>#Wish4u</title>
		<meta http-equiv="content-type" content="text/html; charset=utf-8" />
		<meta name="description" content="" />
		<meta name="keywords" content="" />
		<link href="http://fonts.googleapis.com/css?family=Source+Sans+Pro:300,400" rel="stylesheet" />
		<script src="js/jquery-1.9.1.min.js"></script>
		<script src="css/5grid/init.js?use=mobile,desktop"></script>
		<script src="js/jquery.formerize-1.1.js"></script>
		<script src="js/init.js"></script>
		<noscript>
			<link rel="stylesheet" href="css/5grid/core.css" />
			<link rel="stylesheet" href="css/5grid/core-desktop.css" />
			<link rel="stylesheet" href="css/5grid/core-1200px.css" />
			<link rel="stylesheet" href="css/5grid/core-noscript.css" />
			<link rel="stylesheet" href="css/style.css" />
			<link rel="stylesheet" href="css/style-desktop.css" />
			<link rel="stylesheet" href="css/noscript.css" />
		</noscript>
		<!--[if lte IE 8]><link rel="stylesheet" href="css/ie8.css" /><![endif]-->
	</head>
	<body class="homepage">

		<!-- Wrapper-->
			<div id="wrapper">
				
				<!-- Nav -->
					<nav id="nav">
						<a href="#me" class="icon icon-user active"><span>Home</span></a>
						<a href="#work" class="icon icon-folder"><span>Send a wish</span></a>
						<a href="#email" class="icon icon-mail"><span>SignIn</span></a>
						
					</nav>

				<!-- Main -->
					<div id="main">
						
						<!-- Me -->
							<article id="me" class="panel">
								<header>
									<img src="logohome.png" style="width:18em;">
									
								</header>
								<a href="#work" class="jumplink pic">
									<span class="jumplink arrow icon icon-right"><span>See my work</span></span>
									<img src="images/me.png"  alt="" />
								</a>
							</article>

						<!-- Work --> 
							<article id="work" class="panel">
								<header>
									<h2>Write your wishes:</h2>
								</header>
								<p>
									
								</p>
								<section class="5grid is-gallery">
									
									
									
									<center>

										<?php

										include "dbconnect.php";

										
			
										$sql = "SELECT * FROM utenti ORDER BY id DESC";
										$res = mysql_query($sql, $conn);
										if(mysql_num_rows($res))
											{
	
	
											while ($row = mysql_fetch_array($res))
											{
												echo'
												<a href="index.php?recipient='.$row[id].'#email"><div id="utente"><img src="'.$row[foto].'">'.$row[nome].' '.$row[cognome].'</div></a>
												';
											}
	
	
										}
										

										?>
										
									</center>		
									
									
									
								</section>
							</article>

						<!-- Email -->
							<article id="email" class="panel">
								<header>
									<h2>Send</h2>
								</header>
								<form action="signin.php" method="post">
									<div class="5grid">
										<div class="row">
											<div class="6u">
												<?php echo '<input type="text" class="text" name="id" id="id" placeholder="ID" value="'.$_GET[recipient].'" required/>'; ?>
											</div>
											<div class="6u">
												<input type="text" class="text" name="testo" id="testo" placeholder="Message" required/>
											</div>
										</div>
								
										
										<div class="row">
											<div class="12u">
												<input type="submit" class="button" value="Send" />
											</div>
										</div>
									</div>
								</form>
							</article>

					</div>
		
				<!-- Footer -->
					<div id="footer">
						<ul class="links">
							<li>&copy; FieldEffectLabs.org</li>
							
						</ul>
					</div>
		
			</div>

	</body>
</html>