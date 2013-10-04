(function(){
	"use strict";
	window.App = window.App || {Routers: {}, Collections: {}, Models: {}, Views: {}};

	App.Models.SpuzikAuthModel = Backbone.Model.extend({
		defaults: {
			username: "",
			password: ""
		},
		url: "/new/endpt.php/login"
	});

	App.Views.SpuzikLoginView = Backbone.View.extend({
		model: new App.Models.SpuzikAuthModel(),
		initialize: function(){

		},
		render: function(){
			this.$el.html( $("#loginTemplate").html() );
			return this;
		},
		events:{
			"click .login-button" : "login"
		},
		login: function(){
			alert("login");
			this.model.save({
				username: this.$el.find(".email-signin").val(),
				password: this.$el.find(".password-signin").val()
			},
			{
				success: function(data){
					alert("You are logged in now.");
					//redirect to wall now.
				},
				error: function(){
					alert("You really messed up.");
				}
			});
		}
	});

	App.Views.SpuzikIndexView = Backbone.View.extend({
		initialize: function(){

		},
		render: function(){
			this.$el.html( $("#indexTemplate").html() ); //does not require any parameters.
			return this;
		},
		events: {
			"click .create-account": "createAccount",
			"click .sign-in"  : "loginExpand"
		},
		createAccount: function(event){
			event.stopPropagation();
     	 	event.preventDefault();

			var thisObj = this.$el;
     	 	thisObj.find(".signup-middle").fadeOut("fast",function(){
     	 		thisObj.find(".signup-middle-enter").fadeIn();
     	 	});
     	 	thisObj.find(".info-box").slideDown("slow");
		},
		loginExpand: function(event){
			event.stopPropagation();
     	 	event.preventDefault();

     	 	var thisObj = this.$el;
     	 	thisObj.find(".signup-middle").fadeOut("fast",function(){
     	 		var loginView = new App.Views.SpuzikLoginView();
     	 		thisObj.find(".sign-in-enter").html(loginView.render().el);
     	 		thisObj.find(".sign-in-enter").fadeIn();
     	 	});
		}
	});
}());