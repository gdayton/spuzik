(function(){
	"use strict";
	window.App = window.App || {Views:{}, Collections: {}, Models: {}, Routers: {}};
	App.Models.SpuzikImageModel = Backbone.Model.extend({
		idAttribute: "ImageId",
		defaults:{
			ImageId: "",
			UserId: 0,
			Description: "",
			Date: 0,
			Extension: ""
		},
		urlRoot: "endpt.php/media"
	});

	App.Collections.SpuzikImagesCollection = Backbone.Collection.extend({
		initialize: function(options){
			this.options = options;
		},
		model: App.Models.SpuzikImageModel,
		url: function(){
			return "endpt.php/mediac/"+this.options.UserId;
		}
	});

}());