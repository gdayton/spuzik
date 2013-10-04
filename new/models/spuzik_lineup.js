(function(){
	"use strict";
	window.App = window.App || {Routers: {}, Collections: {}, Models: {}, Views: {}};
	App.Models.SpuzikLineupModel = Backbone.Model.extend({
		idAttribute: "LineupId",
		defaults: {
			LineupId: 0,
			UserId: 0,
			Text: "",
			PhotoURL: "",
			Position: 0
		},
		validate: function(attr){
			var errors = {};
			if(attr.Text === ''){
				errors.Text = "You must enter text into lineup item.";
			}

			if(!_.isEmpty(errors)){
				return errors;
			}
		},
		urlRoot: "endpt.php/lineup"
	});

	App.Collections.SpuzikLineupCollection = Backbone.Collection.extend({
		initialize: function(options){
			this.options = options;
			this.options.vent.on("reloadLineup", function(){ alert("refresh"); }, this);
		},
		model: App.Models.SpuzikLineupModel,
		url: function(){
			return "endpt.php/lineup/"+this.options.UserId;
		}
	});
}());