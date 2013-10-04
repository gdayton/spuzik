(function(){
	"use strict";
	window.App = window.App || {Routers: {}, Collections: {}, Models: {}, Views: {}};
	App.Models.SpuzikUserModel = Backbone.Model.extend({
		defaults: {
			UserId: "",
			FirstName: "",
			LastName: "",
			AccountType: "",
			Email: "",
			LastOn: "",
			ProfileMusicId: "",
			ProfilePicture: "",
			RegistrationDate: "",
			Location: "",
			Nickname: ""
		},
		validate: function(attr){
			var errors = {};
			if(attr.FirstName === ''){
				errors.first_name = "You must enter your first name.";
			}
			if(attr.LastName === ''){
				errors.last_name = "You must enter your last name.";
			}

			/*
			if(attr.location === ''){
				errors.location = "You must enter a location.";
			}
			*/

			if(!_.isEmpty(errors)){
				return errors;
			}
		},
		urlRoot: "endpt.php/user"
	});
}());