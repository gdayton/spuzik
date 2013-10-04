(function(){
	"use strict";
	window.App = window.App || {Routers: {}, Collections: {}, Models: {}, Views: {}};
	App.Models.SpuzikTabAboutMeModel = Backbone.Model.extend({
		initialize: function(options){
			this.options = options;
		},
		idAttribute: "UserId",
		defaults: {
			UserId: "",
			Age: "",
			Location: "",
			Bio: "",
			Nickname: ""
		},
		/*url: function(){
			return "endpt.php/aboutme/"+this.options.UserId;
		}*/
		urlRoot: "endpt.php/aboutme"
	});
})();