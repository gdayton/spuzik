<script>
	var fill = d3.scale.category20();
	var wordsArray = ["Starbucks","Baseball","Hiking","Camping","Programming"];

	reloadFavs();

	function reloadFavs(){
	  d3.layout.cloud().size([450, 500])
		  .words(wordsArray.map(function(d) {
			return {text: d, size: 25}; /* FOR DIFFERENT SIZE TEXT: parseInt(10 + Math.random() * 90) 25*/
		  }))
		  .rotate(function() {
		  	  /*
			  var randomInt = parseInt(Math.random() * 2)
			  if(randomInt == 0){
				return 0;
			  }else{
				return 90;
			  }
			  */
			  return ~~(Math.random() * 5) * 30 - 60;
		  })
		  .font("Impact")
		  .fontSize(function(d) { return d.size; })
		  .on("end", draw)
		  .start();
	}

	function draw(wordsArray) {
		$(".words").html("");
		d3.select(".words").append("svg")
			.attr("width", 500)
			.attr("height", 500)
		  .append("g")
			.attr("transform", "translate(250,250)")
		  .selectAll("text")
			.data(wordsArray)
		  .enter().append("text")
			.style("font-size", function(d) { return d.size + "px"; })
			.style("font-family", "Impact")
			.style("fill", function(d, i) { return fill(i); })
			.attr("text-anchor", "middle")
			.attr("transform", function(d) {
			  return "translate(" + [d.x, d.y] + ")rotate(" + d.rotate + ")";
			})
			.text(function(d) { return d.text; });
	}

	function addWord(){
		var word = $(".fav-word").val();
		if(word != ""){
			wordsArray.push(word);
			reloadFavs();
		}
		$(".fav-word").val("");
		$(".fav-word").select();
	}

	$("input").keypress(function(event) {
		if (event.which == 13) {
			event.preventDefault();
			addWord();
		}
	});
</script>
<style type="text/css">
.words-top{
	text-align:center;
/*
   background-color: #0769D7;
   background-image: -webkit-gradient(linear, 0% 0%, 0% 100%, from(#0769D7), to(#FFF));
   background-image: -webkit-linear-gradient(top, #0769D7, #FFF);
   background-image: -moz-linear-gradient(top, #0769D7, #FFF);
   background-image: -ms-linear-gradient(top, #0769D7, #FFF);
   background-image: -o-linear-gradient(top, #0769D7, #FFF);
   height:50px;
*/
}
.words-bottom{
/*
   background-color: #1a82f7;
   background-image: -webkit-gradient(linear, 0% 0%, 100% 0%, from(#0769D7), to(#FFF));
   background-image: -webkit-linear-gradient(bottom, #0769D7, #FFF);
   background-image: -moz-linear-gradient(bottom, #0769D7, #FFF);
   background-image: -ms-linear-gradient(bottom, #0769D7, #FFF);
   background-image: -o-linear-gradient(bottom, #0769D7, #FFF);
   height:50px;
*/
}
.words{
   /*background-color:grey;*/
   text-align:center;
}
</style>
<div class="words-top">
	<div style="padding-top:20px;">
		<input type="text" placeholder="Favorites..." style="height:26px;" class="fav-word"/><button class="btn btn-small btncustom" style="position:relative; bottom:5px;" onclick="javascript:addWord();">Add</button>
	</div>
</div>
<div class="words"></div>
<div class="words-bottom"></div>