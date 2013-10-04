(function(){
	"use strict";
	window.App = window.App || {Routers: {}, Collections: {}, Models: {}, Views: {}};
	App.Models.SpuzikFavQuoteModel = Backbone.Model.extend({
		idAttribute: "FQLId",
		defaults:{
			FQLId: "",
			Text: "",
			Author: "",
			UserId: 0
		},
		urlRoot: "endpt.php/fq" //fq = favorite quote
	});

	App.Collections.SpuzikFavQuoteCollection = Backbone.Collection.extend({
		initialize: function(options){
			this.options = options;
		},
		model: App.Models.SpuzikFavQuoteModel,
		url: function(){
			return "endpt.php/fqc/"+this.options.UserId;
		}
    });
})();