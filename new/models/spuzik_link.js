(function(){
	"use strict";
	window.App = window.App || {Routers: {}, Collections: {}, Models: {}, Views: {}};
	App.Models.SpuzikLinkModel = Backbone.Model.extend({
		idAttribute: "LinkId",
		defaults: {
			LinkId: "",
			Text: "",
			Url: "",
			UserId: 0
		},
		urlRoot: "endpt.php/link/"
	});

	App.Collections.SpuzikLinksCollection = Backbone.Collection.extend({
		initialize: function(options){
			this.options = options;
		},
		model: App.Models.SpuzikLinkModel,
		url: function(){
			return "endpt.php/links/"+this.options.UserId;
		}
	});
})();