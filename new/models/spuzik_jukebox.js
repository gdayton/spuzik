(function(){
	"use strict";
	window.App = window.App || {Views:{}, Collections: {}, Models: {}, Routers: {}};
	App.Models.SpuzikTuneModel = Backbone.Model.extend({
		idAttribute: "TuneId",
		defaults: {
			TuneId: "",
			Title: "",
			Artist: "",
			Album: "",
			Genre: "",
			Length: "", 	//Length of the song, for example 2:10 for a 2 minute and 10 second song.
			GroovesharkId: "",
			GroovesharkIdArtist: "",
			GroovesharkIdAlbum: ""
		},
		url: "endpt.php/tune"
	});

	App.Collections.SpuzikJukeboxCollection = Backbone.Collection.extend({
		initialize: function(options){
			this.options = options;
		},
		model: App.Models.SpuzikTuneModel,
		url: function(){
			return "endpt.php/tunes/"+this.options.UserId;
		}
	});
}());
/*
var m1 = new App.Models.SpuzikTuneModel({ TuneId:"1", Title:"Racer", Artist:"Giorgio Moroder", Genre:"Electronic", Length:"4:21", GroovesharkId:"123" });
var m2 = new App.Models.SpuzikTuneModel({ TuneId:"2", Title:"123", Artist:"The Rolling Stones", Genre:"Electronic", Length:"4:21", GroovesharkId:"123" });
var m3 = new App.Models.SpuzikTuneModel({ TuneId:"3", Title:"123", Artist:"INXS", Genre:"Electronic", Length:"4:21", GroovesharkId:"123" });
var m4 = new App.Models.SpuzikTuneModel({ TuneId:"4", Title:"This is an extremely long title that will test stuff", Artist:"INXS", Genre:"Electronic", Length:"4:21", GroovesharkId:"123" });
var col = new App.Collections.SpuzikJukeboxCollection();
col.add(m1);
col.add(m2);
col.add(m3);
col.add(m4);
var v1 = new App.Views.SpuzikJukeboxView({collection:col});
$(".music-list table").html(v1.render().el);
*/