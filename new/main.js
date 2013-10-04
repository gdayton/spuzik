/*
var Person = Backbone.Model.extend({
	defaults: {
		name : 'Glenn',
		age : 19,
		occupation : 'student'
	}
});

var template = function(id){
	return _template.$('#'+id).html();
};

var PeopleCollection = Backbone.Collection.extend({
	model: Person
});

className: 'person',
id: 'main', OR YOU CAN USE THESE SELECTORS!
var PersonView = Backbone.View.extend({
	tagName : 'li',
	my_template: template('personTemplate'),
	initialize: function(){
		this.render();
	},
	render: function(){
		this.$el.html(this.my_template(this.model.toJSON()));
	}
});


var PeopleView = Backbone.View.extend({
	tagName:'ul',
	render: function(){
        this.collection.each(function(person){
        	var personView = new PersonView({model: person});
        	this.$el.append(personView.el);
        }, this);
	}
});


(function(){
	window.App = {
		Models: {},
		Collections: {},
		Views: {}
	};

	window.template = function(id){
		return _.template($('#'+id).html());
	};

	App.Models.Person = Backbone.Model.extend({
		name:	"Glenn Dayton",
		age:	19
	});

	App.Views.Person = Backbone.View.extend({
		tagName:'li',
		my_template: template('personTemplate'),
		initialize: function(){
			this.render();
		},render: function(){
			this.$el.html(this.my_template(this.model.toJSON()));
		},events: function(){
			'click':'showAlert'
		},showAlert: function(){
			alert('Pop up thingy.');
		}
	});

	App.Views.People = Backbone.View.extend({
		tagName:'ul',
		render: function(){
			this.collection.each(function(person){
				var pv = new App.Views.Person({model:person});
				this.$el.append(pv.render().el);
			});
		}
	});

	App.Collections.People = Backbone.Collection.extend({
		model: App.Models.Person
	});

})();


SANDBOX

var Game = Backbone.Model.extend({
	initialize: function(){
		alert("oh");
	},
	defaults: {
		name: 'none',
		price: 23
	}
});

var User = Backbone.Model.extend({
	defaults: {
		name: 'null',

	}
});

to create game objects:
var g = new Game({name:"GTA",price:20});

get info from game objects:
g.get('name'); --OR-- g.get('price');

to make changes to game objects:
g.set({name: "Midnight Club"});

make permanent changes to the server:
g.save();

DEVELOPMENT

(function(){
	window.App = {
		Models: {},
		Collections: {},
		Views: {}
	};

	window.template = function(id){
		return _.template($('#' id).html());
	};
})();

SPUZIK BACKBONE.JS CODE
Author: Glenn O Dayton
Date: August 1 2013

Copyright 2013 - Glenn Dayton

(function(){
	window.App  = {
		Views: {},
		Models: {},
		Collections: {}
	};

	window.template = function(temp){
		return _.template($("#"+temp).html());
	}

	App.Views.Person = Backbone.View.extend({
		tagName: 'personHolder',
		m_template: template('personHolder'),
		initialize: function(){
			//VVV -- execute when a jQuery method is called -- VVV
			this.model.on('change',this.render,this);
			this.model.on('destroy',this.remove,this);
		},
		render: function(){
			this.$el.html(this.m_template(this.model.toJSON()));
			return this;
		},
		events:{
			'click':'personExecute',
			'doubleclick .clap':'clapPost'
		},
		personExecute(){
			//alert("personExecute pressed");
			var newName = prompt("Gimme a new fucking name hobag");
			this.model.set('name',newName);
		},
		clapPost(){
			alert("clapPost pressed");
		},
		destroy: function(){
			this.$el.remove();
		}
	});

	App.Views.People = Backbone.View.extend({
		tagName: 'ul',
		initialize: function(){
			this.collection.on('add',this.addOne,this);
		},
		render: function(){
			this.collection.each(this.addOne,this);
		},
		addOne: function(person){
			var personView = new App.Views.Person({model:person});
			this.$el.append(personView.render().el);
		}
	});

	App.Views.PersonAdd = Backbone.View.extend({
		el: '#personAddForm',
		events: {
			'click','addPerson'
		},
		submit: function(e){
			e.preventDefault();
			var newPerson = $(e.currentTarget).find('input[type=text]').val();
			var person = new App.Models.Person({name: newPerson});
			this.collection.add(person);
		}
	});
});


//ROUTER Interface
var AppRouter = Backbone.Router.extend({
	routes: { "*actions": "defaultRoute" // matches http://example.com/#anything-here } });

	var app_router = new AppRouter;
	app_router.on('route:defaultRoute', function(actions) {
		alert(actions);
	});

	Backbone.history.start();
*/
/*
Author: Glenn Dayton
Date: August 1, 2013
*/
(function(){
	window.App = {
		Views: {},
		Models: {},
		Collections: {},
		Routers: {}
	};

	/*
		Misc functions
	*/
	var promptAlert = function(msg, type){
		var color = "";
		if(type == "info"){
			color = "#179bff";
		}else if(type == "error"){
			color = "red";
		}

		$("#info").html(msg);
		$("#info").css("background-color",color);
		$("#info").slideDown("fast", function(){
			setTimeout(function(){
				$("#info").slideUp();
			},500);
		});
	};

	var template = function(temp){
		return _.template($("#"+temp).html());
	};

	//
	//				MODELS
	//

	/*App.Routers.Main = Backbone.Router.extend({
		routes: {
			"":"index",
			"*settings":"settings"
		},
		index: function(){
			alert("index");
		},
		settings: function(){
			alert("settings");
		}
	});*/

	// --- START ---

	var AppRouter = this.Backbone.Router.extend({
		routes: {
			""				: "index",
			"settings"		: "settings",
			"logout"		: "logout",
			"tab/:tab_name"	: "tab",
		},
		index: function(){
			promptAlert("index","info");
		},
		settings: function(){
			promptAlert("settings","info");
		},
		logout: function(){
			promptAlert("logout","info");
		},
		tab: function(tab_name){
			alert(tab_name);
		}
	});

	var app_router = new AppRouter();

	app_router.on('route:defaultRoute', function (actions) {
		alert("yep");
	});

	this.Backbone.history.start();
	/*this.Backbone.history.start({
		pushState: true,
		root: "/",
		silent: true
	});*/

	// --- END ---

	App.Models.FeedItem = Backbone.Model.extend({
		defaults: {
			profile_pic: "null",
			name: "null",
			comment_amount: 0,
			content: "null",
			date: "null",
			claps: 0,
			u_id: 0
		}
	});

	App.Models.RightBar = Backbone.Model.extend({
		defaults: {
			name: "null",
			profile_pic: "null",
			supporting: 0,
			fans: 0
		}
	});

	App.Models.LineupItem = Backbone.Model.extend({
		defaults: {
			lineup: "null",
			position: 0,
			text: "null",
			color: "null"
		}
	});

	App.Models.Quote = Backbone.Model.extend({
		defaults: {
			quote: "null",
			author: "null"
		}
	});

	App.Models.MeTab = Backbone.Model.extend({
		defaults: {
			nickname: "null",
			location: "null",
			gender: "null",
			age_date: "null",
			age: 0
		}
	});

	App.Models.Memory = Backbone.Model.extend({
		defaults: {
			year: "null",
			memory: "null"
		}
	});

	//
	//				COLLECTIONS
	//

	/*
		This collection contains all of the feed items
	  	should be rendered with corresponding view.
	*/
	App.Collections.Feed = Backbone.Collection.extend({
		model: App.Models.FeedItem
	});

	/*
		This container holds all of the lineup items
	*/
	App.Collections.Lineup = Backbone.Collection.extend({
		model: App.Models.LineupItem
	});

	/*
		Generates view for comments within a feed.

	App.Views.Comment = Backbone.View.extend({
		el: ".comments",

	});
	*/

	/*
		Collection for holding quotes models
	*/
	App.Collections.Quotes = Backbone.Collection.extend({
		model: App.Models.Quote
	});

	/*
		Contains all of the memory objects
	*/
	App.Collections.Memories = Backbone.Collection.extend({
		model: App.Models.Memory
	});

	//
	//				VIEWS
	//

	/*
		Mega view

	App.Views.Main = Backbone.View.extend({
		el: "body",
		render: function(){

		}
	});
	*/

	/*
		Individual feed item is generated here.
	*/
	App.Views.Feed = Backbone.View.extend({
		id: 'feed',
		feed_template: template('feedTemplate'),
		events: {
			'click .comment-toggle': 'toggleComment'
		},
		initialize: function(){
			this.render();
		},
		render: function(){
			this.$el.html(this.feed_template(this.model.toJSON()));
			return this;
		},
		toggleComment: function(){
			alert("happened");
		}
	});

	/*
		Appends all of the feed items into feed area.
	*/
	App.Views.FeedArea = Backbone.View.extend({
		el: '#feed-area',
		initialize: function(){
			this.render();
		},
		render: function(){
			this.collection.each(this.addFeed, this);
		},
		addFeed: function(feed){
			var feedView = new App.Views.Feed({model:feed});
			this.$el.append(feedView.render().el);
		}
	});

	/*
		Right hand side, contains lineup view.
	*/
	App.Views.RightBar = Backbone.View.extend({
		el: '.profile-info-holder',
		rs_template: template('profileinfoTemplate'),
		initialize: function(){
			this.render();
		},
		render: function(){
			this.$el.html(this.rs_template(this.model.toJSON()));
			return this;
		}
	});

	/*
		Lineup item view.
	*/
	App.Views.LineupItem = Backbone.View.extend({
		tagName: "li",
		li_template: template("lineupitemTemplate"),
		events:{
			"mouseenter":"showTrash",
			"mouseleave":"hideTrash"
		},
		initialize: function(){
			this.render();
		},
		render: function(){
			this.$el.html(this.li_template(this.model.toJSON()));
			return this;
		},
		showTrash: function(e){
			e.preventDefault();
			this.$(".lineup-trash").show();
		},
		hideTrash: function(e){
			e.preventDefault();
			this.$(".lineup-trash").hide();
		}
	});

	/*
		Lineup area.
	*/
	App.Views.Lineup = Backbone.View.extend({
		el: '.lineup ol',
		initialize: function(){
			this.render();
		},
		render: function(){
			this.collection.each(this.addLineup, this);
		},
		addLineup: function(lineup){
			var lineupView = new App.Views.LineupItem({ model:lineup });
			this.$el.append(lineupView.render().el);
		}
	});

	/*
		Render the me tab information
	*/
	App.Views.MeTab = Backbone.View.extend({
		el: '#tab-content',
		metab_template: template('meTemplate'),
		initialize: function(){
			this.render();
		},
		render: function(){
			this.$el.html(this.metab_template(this.model.toJSON()));
			return this;
		}
	});

	/*
		Render the quotes view
	*/
	App.Views.Quote = Backbone.View.extend({
		tagName: 'li',
		quote_template: template('quoteTemplate'),
		initialize: function(){
			this.render();
		},
		render: function(){
			this.$el.html(this.quote_template(this.model.toJSON()));
			return this;
		}
	});

	/*
		Render all of the quotes now
	*/
	App.Views.Quotes = Backbone.View.extend({
		el: '.user-quotes-ul',
		initialize: function(){
			this.render();
		},
		render: function(){
			this.collection.each(this.addQuote, this);
		},
		addQuote: function(quote){
			var quoteView = new App.Views.Quote({model:quote});
			this.$el.append(quoteView.render().el);
		}
	});

	/*
		Render the memory view
	*/
	App.Views.Memory = Backbone.View.extend({
		tagName: 'tr',
		memory_template: template('memoryTemplate'),
		initialize: function(){
			this.render();
		},
		render: function(){
			this.$el.html(this.memory_template(this.model.toJSON()));
			return this;
		}
	});

	/*
		Render the Memory holder
	*/
	App.Views.Memories = Backbone.View.extend({
		el: '.memory-table',
		initialize: function(){
			this.render();
		},
		render: function(){
			this.collection.each(this.addMemory, this);
		},
		addMemory: function(memory){
			var memoryView = new App.Views.Memory({model:memory});
			this.$el.append(memoryView.render().el);
		}
	});

})(jQuery);

/*
TEST CODE

//FEED

var f1 = new App.Models.FeedItem({ profile_pic: "http://54.243.129.126/usr_content/pics/5200107f1114d_w.jpg", name: "Harry", comment_amount: 23, content: "And our third signing- Nacer Chadli. With these players and Bale in the team, I see no reason why we cant be a real handful for all the top 4 teams. <img src='http://54.243.129.126/usr_content/pics/5200107f1114d_w.jpg' />", date: "4 months ago", claps:34});
var f2 = new App.Models.FeedItem({ profile_pic: "http://54.243.129.126/usr_content/pics/5200107f1114d_w.jpg", name: "Jake Cohen", comment_amount: 13, content: "This is a really cool website, yeper oo", date: "2 months ago", claps:89});
var f3 = new App.Models.FeedItem({ profile_pic: "http://54.243.129.126/usr_content/pics/5200107f1114d_w.jpg", name: "Jake Cohen", comment_amount: 13, content: "This is a really cool website, yeper oo", date: "2 months ago", claps:89});
var f4 = new App.Models.FeedItem({ profile_pic: "http://54.243.129.126/usr_content/pics/5200107f1114d_w.jpg", name: "Jake Cohen", comment_amount: 13, content: "<img src='http://54.243.129.126/usr_content/pics/51eb37bc9ee25_w.jpg' />", date: "2 months ago", claps:89});
var col = new App.Collections.Feed();
col.add(f1);
col.add(f2);
col.add(f3);
col.add(f4);
var view = new App.Views.FeedArea({ collection:col });

//RIGHTBAR

var info = new App.Models.RightBar({ name: "Glenn Dayton", profile_pic: "http://54.243.129.126/usr_content/pics/50f8a372b1bfe_t.jpg", supporting: 34, fans: 65 });
var view = new App.Views.RightBar({ model:info });

//LINEUP

var li1 = new App.Models.LineupItem({ lineup: "The Rolling Stones", position:1, color:"blue", font:"helvetica"});
var li2 = new App.Models.LineupItem({ lineup: "INXS", position:2, color:"red", font:"helvetica"});
var li3 = new App.Models.LineupItem({ lineup: "Bob Dylan", position:3, color:"orange", font:"helvetica"});
var li4 = new App.Models.LineupItem({ lineup: "Red Bull", position:1, color:"blue", font:"helvetica"});
var li5 = new App.Models.LineupItem({ lineup: "Car paint", position:2, color:"red", font:"helvetica"});
var li6 = new App.Models.LineupItem({ lineup: "Tsunami", position:3, color:"green", font:"helvetica"});
var li7 = new App.Models.LineupItem({ lineup: "INXS", position:2, color:"red", font:"helvetica"});
var li8 = new App.Models.LineupItem({ lineup: "Bob Dylan", position:3, color:"orange", font:"helvetica"});
var li9 = new App.Models.LineupItem({ lineup: "Red Bull", position:1, color:"blue", font:"helvetica"});
var li10 = new App.Models.LineupItem({ lineup: "Car paint", position:2, color:"red", font:"helvetica"});
var li11 = new App.Models.LineupItem({ lineup: "Tsunami", position:3, color:"green", font:"helvetica"});
var col = new App.Collections.Lineup();
col.add(li1);
col.add(li2);
col.add(li3);
col.add(li4);
col.add(li5);
col.add(li6);
col.add(li7);
col.add(li8);
col.add(li9);
col.add(li10);
col.add(li11);
var view = new App.Views.Lineup({ collection:col });

//ME TAB

var me = new App.Models.MeTab({ nickname: "Fizzle De, Fizzle Do", location: "San Diego, CA", gender: "Male", age_date: "Jan 19, 1994", age: 19 });
var view_me = new App.Views.MeTab({ model:me });

//ME TAB QUOTES SECTION

var qu1 = new App.Models.Quote({ quote: "This is neat", author: "Bob Filner"});
var qu2 = new App.Models.Quote({ quote: "Aw man I'm gone now", author: "Bob Filner"});
var qcol = new App.Collections.Quotes();
qcol.add(qu1);
qcol.add(qu2);
var qview = new App.Views.Quotes({ collection: qcol });

//ME TAB MEMORY ZONE

var mem1 = new App.Models.Memory({ year: "2006", memory: "I remember going into middle school"});
var mem2 = new App.Models.Memory({ year: "2005", memory: "Went to Saftey Patrol camp on mount palomar"});
var qmem = new App.Collections.Memories();
qmem.add(mem1);
qmem.add(mem2);
var memview = new App.Views.Memories({ collection: qmem});

$("#info").hide();
*/