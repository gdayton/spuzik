(function(){
	"use strict";
	window.App = window.App || {Routers: {}, Collections: {}, Models: {}, Views: {}};
	App.Views.SpuzikTopView = Backbone.View.extend({
		initialize: function(options){
			this.options = options;
		},
		render: function(){
			this.$el.html( _.template( $("#topTemplate").html(), {UserId: this.options.UserId } ) );
			if(this.model == null){
				var second = new App.Views.SpuzikTabSlideshowView();
				this.$el.find(".img-cons").html(second.render().el);
			}
			if(this.model == "me"){
				var second = new App.Views.SpuzikTabAboutMeView({ vent: this.options.vent, view: this.options.view, UserId: this.options.UserId });
				this.$el.find(".img-cons").html(second.render().el);
				this.$el.find(".navigation .me").prepend("<div class='arrow-left'></div>");
				this.$el.find(".navigation .me").css("background-color","#eee");
			}
			if(this.model == "media"){
				var second = new App.Views.SpuzikTabMediaView({ vent: this.options.vent, view: this.options.view, UserId: this.options.UserId });
				this.$el.find(".img-cons").html(second.render().el);
				this.$el.find(".navigation .media").prepend("<div class='arrow-left'></div>");
				this.$el.find(".navigation .media").css("background-color","#eee");
			}
			if(this.model == "myTunes"){
				var second = new App.Views.SpuzikTabMyTunesView();
				this.$el.find(".img-cons").html(second.render().el);
				this.$el.find(".navigation .myTunes").prepend("<div class='arrow-left'></div>");
				this.$el.find(".navigation .myTunes").css("background-color","#eee");
			}
			if(this.model == "links"){
				var second = new App.Views.SpuzikTabLinksView({ vent: this.options.vent, view: this.options.view, UserId: this.options.UserId });
				this.$el.find(".img-cons").html(second.render().el);
				this.$el.find(".navigation .links").prepend("<div class='arrow-left'></div>");
				this.$el.find(".navigation .links").css("background-color","#eee");
			}
			if(this.model == "live"){
				var second = new App.Views.SpuzikTabLiveView();
				this.$el.find(".img-cons").html(second.render().el);
				this.$el.find(".navigation .live").prepend("<div class='arrow-left'></div>");
				this.$el.find(".navigation .live").css("background-color","#eee");
			}
			if(this.model == "zoneOut"){
				var second = new App.Views.SpuzikTabZoneOutView();
				this.$el.find(".img-cons").html(second.render().el);
				this.$el.find(".navigation .zoneOut").prepend("<div class='arrow-left'></div>");
				this.$el.find(".navigation .zoneOut").css("background-color","#eee");

				//setup the modal down here.
				/*var modal = new App.Views.SpuzikPhotoModal();
				this.$el.find("#img-popup").*/
			}
			return this;
		}
	});
}());