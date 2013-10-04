(function(){
	"use strict";
	window.App = window.App || {Routers: {}, Collections: {}, Models: {}, Views: {}};
	App.Views.SpuzikHeaderView = Backbone.View.extend({
		initialize: function(){

		},
		render: function(){
			this.$el.html( $("#headerTemplate").html() );
			return this;
		},
		events: {
			"mouseenter .header-functions .right": "toggleHeaderRightCollapse",
			"mouseleave .header-functions .right": "toggleHeaderRightExpand",
			"mouseenter .header-functions .left": "toggleHeaderLeftCollapse",
			"mouseleave .header-functions .left": "toggleHeaderLeftExpand",
			"click .user-login, .user-menu-big": "toggleUserMenu"
		},
		toggleHeaderRightCollapse: function(){
			$(".header-functions .left").css("width","50px");
			$(".header-functions .right .show-expanded").fadeIn("fast");
		},
		toggleHeaderRightExpand: function(){
			$(".header-functions .left").css("width","");
			$(".header-functions .right .show-expanded").hide();
		},
		toggleHeaderLeftCollapse: function(){
			$(".header-functions .right").css("width","50px");
			$(".header-functions .left .show-expanded").fadeIn("fast");
			$(".search-bar").focus();
		},
		toggleHeaderLeftExpand: function(){
			$(".header-functions .right").css("width","");
			$(".header-functions .left .show-expanded").hide();
		},
		toggleUserMenu: function(){
			$(".user-menu").toggle();
		}
	});
}());


//alert("Planned to do when I get back:\n-Make the search bar bigger.\n-Put the rest of the music player in.\n-Change recomendations to suggestions.\n-Change jukebox to my tunes.\n-Add express yourself in.\n-Design the rest of all the tabs.\n-Consider this bitch done.");

/*
REFER TO THIS FOR MAKING THE LINEUP VIEW
$(document).ready(function(){
	$(".lineup-item").mouseenter(function(){
		var img_url = $(this).attr("data-img");
		$(this).css("background-image","url('"+img_url+"')");
	}).mouseleave(function(){
		$(this).css("background-image","");
	});
});
*/