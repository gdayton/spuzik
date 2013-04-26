/*function findAndPlaySong(searchString) {
	$.ajax({
		url: 'api/idGetter.php?query=' + searchString,
		dataType: 'jsonp',
		success: function(data) {
		playSong(data.SongID);
	  }
	});
}

function pauseMusic() {
	window.player.pauseStream();
}

function resumeMusic() {
	window.player.resumeStream();
}

var doc = $(document);

doc.on("click", "a[data-songid]", function(e) {
	e.preventDefault();
	playSong($(this).data("songid"));
});

doc.on("click", ".pause", function() {
	pauseMusic();
});

doc.on("click", ".resume", function() {
	resumeMusic();
});

doc.on("click", ".search-song", function(e) {
	e.preventDefault();
	findAndPlaySong($("#song-search-input").val());
});

(function($) {

	function playSong(songID) {
		$.ajax({
		  url: "api/songGetter.php",
		  type: "POST",
		  data: {
		  	song: songID
		  },
		  success: function(response) {
		    var responseData = $.parseJSON(response);
		    window.player.playStreamKey(responseData.StreamKey, responseData.StreamServerHostname, responseData.StreamServerID);
		  }
		});
	}

	function findAndPlaySong(searchString) {
		$.ajax({
			url: 'api/idGetter.php?query=' + searchString,
			dataType: 'jsonp',
			success: function(data) {
		  	playSong(data.SongID);
		  }
		});
	}

	function pauseMusic() {
		window.player.pauseStream();
	}

	function resumeMusic() {
		window.player.resumeStream();
	}

	var doc = $(document);

	doc.on("click", "a[data-songid]", function(e) {
		e.preventDefault();
		playSong($(this).data("songid"));
	});

	doc.on("click", ".pause", function() {
		pauseMusic();
	});

	doc.on("click", ".resume", function() {
		resumeMusic();
	});

	doc.on("click", ".search-song", function(e) {
		e.preventDefault();
		findAndPlaySong($("#song-search-input").val());
	});

})(jQuery);*/