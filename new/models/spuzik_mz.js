(function(){
	"use strict";
	window.App = window.App || {Routers: {}, Collections: {}, Models: {}, Views: {}};
	App.Models.SpuzikMemZoneModel = Backbone.Model.extend({
		idAttribute: "MemId",
		defaults:{
			MemId: "",
			Text: "",
			Date: "",
			UserId: 0
		},
		urlRoot: "endpt.php/mz" //mz = memory zone
	});

	App.Collections.SpuzikMemZoneCollection = Backbone.Collection.extend({
		initialize: function(options){
			this.options = options;
		},
		model: App.Models.SpuzikMemZoneModel,
		url: function(){
			return "endpt.php/mzc/"+this.options.UserId;
		}
	});
})();