(function(){
	"use strict";
	window.App = window.App || {Views:{}, Collections: {}, Models: {}, Routers: {}};
	App.Views.SpuzikJukeboxView = Backbone.View.extend({
		tagName: "table",
		initialize: function(options){
			this.options = options;
		},render: function(){
			var container = document.createDocumentFragment();
			var self = this;
			/*
			this.collection.fetch(function(model){
				var tuneView = new App.Views.SpuzikJukeboxIndvView({ model:model, vent: self.options.vent, view: self.options.view});

				container.appendChild(tuneView.render().el);
			}, this);
			*/
			this.collection.each(function(model){
				var tuneView = new App.Views.SpuzikJukeboxIndvView({ model:model, vent: self.options.vent, view: self.options.view});

				container.appendChild(tuneView.render().el);
			}, this);

			//this.$el.find(".music-list table").append(container);
			this.$el.append(container);
			return this;
		},
		events:{

		},
		attributes: function(){
			return {
				'cellpadding': '5',
				'cellspacing': '0',
				'width': '100%',
				'border': '0'
			}
		}
	});

	App.Views.SpuzikJukeboxIndvView = Backbone.View.extend({
		tagName: "tr",
		initialize: function(options){
			this.options = options;
		}, render: function(){
			this.$el.html(_.template($("#jukeboxItem").html(), this.model.toJSON()));
			return this;
		},
		events:{
			"click .song-actions": "optionsDrop"
		},
		optionsDrop: function(){
			//this.$el.find(".song-actions-view").slideToggle();
			var self = this;
			this.$el.find(".song-actions-view").animate({width: 'toggle'}, function(){
				//is open, must close it.
				if(self.$el.find(".song-actions").attr("tog") == "open"){
					self.$el.find(".song-actions").removeClass("glyphicon-chevron-right");
					self.$el.find(".song-actions").addClass("glyphicon-chevron-left");
					self.$el.find(".song-actions").attr("tog","close");
				}else{
					self.$el.find(".song-actions").removeClass("glyphicon-chevron-left");
					self.$el.find(".song-actions").addClass("glyphicon-chevron-right");
					self.$el.find(".song-actions").attr("tog","open");
				}
			});
		}
	});

	App.Views.SpuzikJukeboxSearchView = Backbone.View.extend({
		tagName: "tr",
		initialize: function(options){
			this.options = options;
		}, render: function(){
			this.$el.html(_.template($("#tabProspectJukeboxIndv").html(), this.model.toJSON()));
			return this;
		},
		events:{
			"click .add-tune": "addTune"
		},
		addTune: function(){
			alert("Add this tune.");
		}
	});
}());