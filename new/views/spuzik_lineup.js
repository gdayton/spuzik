(function(){
	"use strict";
	window.App = window.App || {Views:{}, Collections: {}, Models: {}, Routers: {}};
	App.Views.SpuzikLineupView = Backbone.View.extend({
		className: 'lineup-container ui-state-default',
		initialize: function(options){
			//_.bindAll(this, "reloadLineup");
			this.options = options;
			this.options.vent.on("reloadLineup", this.addLineupItem, this);
			this.collection.on("reset", this.render, this);
		},
		events: {
			//"drop": "drop"
		},
		render: function(){
			//only do this if you are logged in though
			this.collection.each(this.addLineup, this);

			return this;
		},
		addLineup: function(lineupItem){
			var lineupIndvView = new App.Views.SpuzikLineupIndvView({ model: lineupItem, view: this.options.view, vent: this.options.vent });
			this.$el.append(lineupIndvView.render().el);
		},
		addLineupItem: function(li){
			li.save();
			this.collection.fetch();
		},
		removeLineupItem: function(){

		}
		/*drop: function(event, id){
			alert("Position Id"+id);
		},*/
	});

	App.Views.SpuzikLineupIndvView = Backbone.View.extend({
		tagName: 'div',
		className: 'ui-state-default',
		initialize: function(options){
			this.options = options;
			this.model.bind('change', this.render, this);
            this.model.bind('destroy', this.remove, this);
		},
		render: function(){
			this.$el.html( _.template( $("#lineupItemTemplate").html(), this.model.toJSON() ) );
			if(!this.options.view){  //if this is true then remove the ability to remove and move the lineup items.
				this.$el.find(".lineup-floater").hide();
			}
			return this;
		},
		events: {
			//Uncomment to enable background image toggling.
			/*"mouseenter .lineup-item": "toggleLineupImgShow",
			"mouseleave .lineup-item": "toggleLineupImgHide"*/
			"click .delete-lineup" : "deleteLineupItem"
		},
		toggleLineupImgShow: function(ev){
			var img_url = $(ev.target).parent().attr("data-img");
			$(ev.target).parent().css("background-image","url('"+img_url+"')");
		},
		toggleLineupImgHide: function(ev){
			$(ev.target).parent().css("background-image","");
		},
		deleteLineupItem: function(){
			var yesno = confirm("Are you sure you want to delete this lineup item?");
			if(yesno){
				this.model.destroy({
					success: function(){
						alert("deleted the lineup item");
					}
				});
			}
		},
		remove: function(){
			$(this.el).remove();
		}

	});

	App.Views.SpuzikAddLineupView = Backbone.View.extend({
		initialize: function(options){
			this.options = options;
		},
		render: function(){
			this.$el.html($("#lineupAddItemTemplate").html());
			return this;
		},
		events: {
			'keypress input[type=text]' : 'addLineupItemTop'
		},
		addLineupItemTop: function(e){
			if (e.keyCode != 13) return;
        	this.addLineupItem(e);
		},
		addLineupItem: function(e){
			var lineupItem = new App.Models.SpuzikLineupModel({
				LineupId: "123",
				Text: this.$el.find("input").val(),
				UserId: 0,
				Position:0,
				PhotoURL: "this"
			});
			//lineupItem.save();
			this.$el.find("input").val("");
			this.$el.find("input").focus();

			this.options.vent.trigger("reloadLineup", lineupItem);
		}
	});
}());