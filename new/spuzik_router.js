(function(){
	"use strict";
	window.App = window.App || {Routers: {}, Collections: {}, Models: {}, Views: {}};
	var vent = _.extend({}, Backbone.Events);

	App.Routers.SpuzikRouter = Backbone.Router.extend({
		routes: {
			""							: "index",
			"p/:profile_id"				: "profile_withoutargs",
			"p/:profile_id/:tab_name"	: "profile",
			"photo/:photo_id"			: "photo",
			"settings"					: "settings"
		},

		initialize: function(){

		},

		profile_withoutargs: function(profile_id){
			this.profile(profile_id, null);
		},

		profile: function(profile_id, tab_name){
			var own_account = false;

			$.ajax({
				type: 'GET',
				url: '/new/endpt.php/login',
				dataType: "json",
				success: function(data){
					if(data.login_status){
						if(data.user.UserId == profile_id){
							this.currentView = new App.Views.SpuzikProfileView({ model:[tab_name, profile_id, true, vent] });
							$("#mega-holder").html(this.currentView.render().el);
						}else{
							this.currentView = new App.Views.SpuzikProfileView({ model:[tab_name, profile_id, false, vent] });
							$("#mega-holder").html(this.currentView.render().el);
						}
					}else{
						window.location = "/new";
					}
				}
			});
		},

		photo: function(photo_id){
			alert("Photo id: "+photo_id);
		},

		settings: function(){
			alert("called settings");
			//this.currentView = new App.Views.SpuzikSettingsView();
		},

		index: function(){
			// Redirect user if they are logged in to the profile.
			$.ajax({
				type: 'GET',
				url: '/new/endpt.php/login',
				dataType: "json",
				success: function(data){
					if(data.login_status){
						window.location = "#/p/"+data.user.UserId;
						return 0;
					}
				}
			});

			this.currentView = new App.Views.SpuzikIndexView();
			$("#mega-holder").html(this.currentView.render().el);
		}
	});
}());
/*
(function () {
  "use strict";
  window.APP = window.APP || {Routers: {}, Collections: {}, Models: {}, Views: {}};
  APP.Routers.NoteRouter = Backbone.Router.extend({
    routes: {
      "note/new": "create",
      "notes/index": "index",
      "note/:id/edit": "edit",
      "note/:id/view": "show"
    },

    initialize: function (options) {
      this.notes = options.notes;
      // this is debug only to demonstrate how the backbone collection / models work
      this.notes.bind('reset', this.updateDebug, this);
      this.notes.bind('add', this.updateDebug, this);
      this.notes.bind('remove', this.updateDebug, this);
      this.index();
    },

    updateDebug: function () {
      $('#output').text(JSON.stringify(this.notes.toJSON(), null, 4));
      // .animate({scrollTop: $('#offset').scrollHeight}, 1000);
    },

    create: function () {
      this.currentView = new APP.Views.NoteNewView({notes: this.notes, note: new APP.Models.NoteModel()});
      $('#primary-content').html(this.currentView.render().el);
    },

    edit: function (id) {
      var note = this.notes.get(id);
      this.currentView = new APP.Views.NoteEditView({note: note});
      $('#primary-content').html(this.currentView.render().el);
    },

    show: function (id) {
      var note = this.notes.get(id);
      this.currentView = new APP.Views.NoteShowView({note: note});
      $('#primary-content').html(this.currentView.render().el);
    },

    index: function () {
      this.currentView = new APP.Views.NoteIndexView({notes: this.notes});
      $('#primary-content').html(this.currentView.render().el);
      // we would call to the index with
      // this.notes.fetch()
      // to pull down the index json response to populate our collection initially
    }
  });
}());
*/