/*
 * Copyright (c)2013 Glenn Dayton
 */
(function(){
	"use strict";
	window.App = window.App || {Routers: {}, Collections: {}, Models: {}, Views: {}};

	App.Views.SpuzikTabSlideshowView = Backbone.View.extend({
		initialize: function(){

		},
		render: function(){
			this.$el.html( $("#tabSlideshowTemplate").html() );
			return this;
		}
	});

	/*
		Show the favorite quotes & lyrics           ==========================================================
	*/
	App.Views.SpuzikTabFavQuoteView = Backbone.View.extend({
		initalize: function(options){
			this.options = options;
			this.collection.on("update", this.render);
		},
		events:{
			"click .add-fq": "dropAdd",
			"click .collapse-fq-cancel": "dropClose",
			"click .fq-save": "add"
		},
		render: function(){
			this.options.vent.on("removeFQ", this.removeFQ, this);
			this.$el.html($("#tabFavQuoteTemplate").html());
			if(!this.options.view){
				this.$el.find(".add-fq").remove();
			}
			//console.log(this.collection);
			//this.collection.each(this.addFavQuoteIndv, this);

			var container = document.createDocumentFragment();
			var self = this;

			if(this.collection.length > 0){
				this.collection.each(function(model){
					var fqIndvView = new App.Views.SpuzikTabFavQuoteIndvView({model:model, vent: self.options.vent, view: self.options.view});
					container.appendChild(fqIndvView.render().el);
				}, this);
				this.$el.find(".favQuoteHolder").append(container);
			}else{
				this.$el.find(".favQuoteHolder").prev().append("<div class='no-fq'><span class='glyphicon glyphicon-exclamation-sign'></span> No favorite quotes or lyrics have been added.</div>");
			}

			return this;
		},
		dropAdd: function(){
			this.$el.find(".add-fq").hide();
			this.$el.find(".add-fq-hidden").slideToggle();
		},
		dropClose: function(){
			this.$el.find(".add-fq-hidden .fq-text").val("");
			this.$el.find(".add-fq-hidden .fq-author").val("");
			var self = this;
			this.$el.find(".add-fq-hidden").slideUp("fast",function(){
				self.$el.find(".add-fq").show();
			});
		},
		add: function(){
			//possibly refresh the entire fq object here and add it with the righ FQLId for deletion to work right.
			var self = this;
			this.collection.create({
				FQLId: "1",
				UserId: "1",
				Text: this.$el.find(".fq-text").val(),
				Author: this.$el.find(".fq-author").val()
			},{
				silent: true,
				wait:true,
				success: function(model, response){
					self.dropClose();
					self.render();
				},error: function(){
					alert("error");
				}
			});
		},
		removeFQ: function(model){
			this.collection.remove(model);
			model.destroy();
		}
	});

	/*
		Show the memory zone
	*/
	App.Views.SpuzikTabMemZoneView = Backbone.View.extend({
		initialize: function(options){
			this.options = options;
			this.collection.on("update", this.render);
		},
		events:{
			"click .add-mem": "dropAdd",
			"click .collapse-mem-cancel": "dropClose",
			"click .mem-save": "add"
		},
		render: function(){
			this.options.vent.on("removeMEM", this.removeMEM, this);
			this.$el.html($("#tabMemZoneTemplate").html());

			if(!this.options.view){
				this.$el.find(".add-mem").remove();
			}

			var container = document.createDocumentFragment();
			var self = this;

			if(this.collection.length > 0){
				this.collection.each(function(model){
					var memIndvView = new App.Views.SpuzikTabMemZoneIndvView({model:model, vent: self.options.vent, view: self.options.view});
					container.appendChild(memIndvView.render().el);
				}, this);
				this.$el.find(".memZoneHolder").append(container);
			}else{
				this.$el.find(".memZoneHolder").prev().append("<div class='no-mem'><span class='glyphicon glyphicon-exclamation-sign'></span> No memories have been added.</div>");
			}

			return this;
		},
		dropAdd: function(){
			this.$el.find(".add-mem").hide();
			this.$el.find(".add-mem-hidden").slideToggle();
		},
		dropClose: function(){
			this.$el.find(".add-mem-hidden .mem-text").val("");
			this.$el.find(".add-mem-hidden .mem-date").val("");
			var self = this;
			this.$el.find(".add-mem-hidden").slideUp("fast",function(){
				self.$el.find(".add-mem").show();
			});
		},
		add: function(){
			//possibly refresh the entire fq object here and add it with the righ MEMId for deletion to work right.
			var self = this;
			this.collection.create({
				MemId: "1",
				UserId: "1",
				Text: this.$el.find(".mem-text").val(),
				Date: this.$el.find(".mem-date").val()
			},{
				silent: true,
				wait:true,
				success: function(model, response){
					self.dropClose();
					self.render();
				},error: function(){
					alert("error");
				}
			});
		},
		removeMEM: function(model){
			this.collection.remove(model);
			model.destroy();
		}
	});

	/*
		Individual FQ item           ==========================================================
	*/
	App.Views.SpuzikTabFavQuoteIndvView = Backbone.View.extend({
		tagName: "li",
		initialize: function(options){
			this.options = options;
		},
		render: function(){
			this.$el.html( _.template( $("#tabFavQuoteIndvTemplate").html(), this.model.toJSON() ) );

			if(!this.options.view){
				this.$el.find(".fq-remove").remove();
			}

			return this;
		},
		events: {
			"click .fq-remove": "remove"
		},
		remove: function(){
			this.options.vent.trigger("removeFQ", this.model);
			this.removeView();
		},
		removeView: function(){
			this.$el.remove();
		}
	});

	/*
		Individual Mem item
	*/
	App.Views.SpuzikTabMemZoneIndvView = Backbone.View.extend({
		tagName: "tr",
		initialize: function(options){
			this.options = options;
		},
		render: function(){
			this.$el.html( _.template( $("#tabMemZoneIndvTemplate").html(), this.model.toJSON() ) );

			if(!this.options.view){
				this.$el.find(".mem-remove").remove();
			}

			return this;
		},
		events:{
			"click .mem-remove": "remove"
		},
		remove: function(){
			this.options.vent.trigger("removeMEM", this.model);
			this.removeView();
		},
		removeView: function(){
			this.$el.remove();
		}
	});

	/*
		Takes the model for display purposes.
	*/
	App.Views.SpuzikTabAboutMeInfoView = Backbone.View.extend({
		initialize: function(options){
			//vent, view, and model
			this.options = options;
		},
		events: {
			"click .edit-aboutme": "triggerChange"
		},
		render: function(){
			this.$el.html( _.template($("#tabAboutMeInfoTemplate").html(), this.model.toJSON()) );
			if(!this.options.view){
				//remove the edit button
				this.$el.find(".edit-aboutme").hide();
			}
			return this;
		},
		triggerChange: function(){
			this.options.vent.trigger("editClick");
		}
	});

	/*
		Takes the model for editing purposes.
	*/
	App.Views.SpuzikTabAboutMeEditView = Backbone.View.extend({
		initialize: function(options){
			this.options = options;
		},
		events: {
			"click .edit-save": "triggerChange"
		},
		render: function(){
			this.$el.html( _.template($("#tabAboutMeEditTemplate").html(), this.model.toJSON()) );
			return this;
		},
		triggerChange: function(){
			this.model.set({
				Age: this.$el.find(".aboutme-age").val(),
				Location: this.$el.find(".aboutme-location").val(),
				Bio: this.$el.find(".aboutme-bio").val(),
				Nickname: this.$el.find(".aboutme-nickname").val()
			});
			this.model.save();
		}
	});

	App.Views.SpuzikTabAboutMeView = Backbone.View.extend({
		initialize: function(options){
			_.bindAll(this,"successCallback","errorCallback","successCallbackMem","errorCallbackMem");
			this.options = options;
			this.options.vent.on("editClick", this.addEditInfo, this);

			//Keep model view out here, so that you can branch it for edit and view purposes.
			this.aboutMeModel = new App.Models.SpuzikTabAboutMeModel({ UserId: this.options.UserId });
			this.aboutMeModel.fetch(); //will grab the about me information according to specified id.

			this.favQuotesCollection = new App.Collections.SpuzikFavQuoteCollection({ UserId: this.options.UserId });
			//this.favQuotesCollection = new App.Collections.SpuzikFavQuoteCollection([{"FQLId":"randomid123","Text":"Sometimes the best things are the things that are cheap.","Author":"Glenn Dayton","UserId":"1"},{"FQLId":"randomid1234","Text":"Something really cool.","Author":"Steve Jobs","UserId":"1"}]);

			this.memZoneCollection = new App.Collections.SpuzikMemZoneCollection({ UserId: this.options.UserId });
			//Could improve by adding date as a range for this.
			/*this.memZoneCollection = new App.Collections.SpuzikMemZoneCollection([
				{MemId: "random123", Text: "I love sbucks", Date: "2013", UserId: 1},
				{MemId: "random23", Text: "I love coffee", Date: "2012", UserId: 1}
			]);*/

			this.aboutMeModel.on("change", this.render, this);
		},
		render: function(){
			this.$el.html( $("#tabAboutMeTemplate").html() );

			//rendering/attaching info
			this.addInfo();

			this.favQuotesCollection.fetch({
				success: this.successCallback,
				error: this.errorCallback
			});

			this.memZoneCollection.fetch({
				success: this.successCallbackMem,
				error: this.errorCallbackMem
			});

			//render fav quotes area
			/*console.log("Inside render");
			console.log(this.favQuotesCollectionTransporter);
			this.favQuotes = new App.Views.SpuzikTabFavQuoteView({ collection: this.favQuotesCollection, vent: this.options.vent, view: this.options.view });
			this.$el.find(".favquote").html(this.favQuotes.render().el);*/

			//render mem zone area
			/*var memZone = new App.Views.SpuzikTabMemZoneView({ collection: this.memZoneCollection, vent: this.options.vent, view: this.options.view });
			this.$el.find(".memzone").html(memZone.render().el);*/

			return this;
		},
		addFavQuote: function(){
			this.favQuotes = new App.Views.SpuzikTabFavQuoteView({ collection: this.favQuotesCollection, vent: this.options.vent, view: this.options.view });
			this.$el.find(".favquote").html(this.favQuotes.render().el);
		},
		addInfo: function(){
			var aboutMeInfo = new App.Views.SpuzikTabAboutMeInfoView({ model: this.aboutMeModel, vent: this.options.vent, view: this.options.view });
			this.$el.find(".aboutmeholder").html(aboutMeInfo.render().el);
		},
		addEditInfo: function(){
			var aboutMeInfo = new App.Views.SpuzikTabAboutMeEditView({ model: this.aboutMeModel, vent: this.options.vent, view: this.options.view });
			this.$el.find(".aboutmeholder").html(aboutMeInfo.render().el);
		},
		successCallback: function(collection){
			var favQuotes = new App.Views.SpuzikTabFavQuoteView({ collection: collection, vent: this.options.vent, view: this.options.view });
			this.$el.find(".favquote").html(favQuotes.render().el);
		},
		errorCallback: function(model){
			alert("error Favorite quotes");
		},
		successCallbackMem: function(collection){
			var memZone = new App.Views.SpuzikTabMemZoneView({ collection: collection, vent: this.options.vent, view: this.options.view });
			this.$el.find(".memzone").html(memZone.render().el);
		},
		errorCallbackMem: function(model){
			alert("error Memory zone.");
		}
	});

	App.Views.SpuzikTabMediaView = Backbone.View.extend({
		initialize: function(options){
			this.options = options;
			this.collection = new App.Collections.SpuzikImagesCollection({ UserId: this.options.UserId });
		},
		render: function(){
			this.options.vent.on("update-feed", this.render, this);
			this.$el.html( $("#tabMediaTemplate").html() );
			var self = this;
			this.$el.find('#fileupload').fileupload({
				dataType: 'json',
				done: function (e, data) {
					$.each(data.result.files, function (index, file) {
						var descView = new App.Views.SpuzikTabMediaDescription({ model: file.name, view: self.options.view, vent: self.options.vent, UserId: self.options.UserId });
						self.$el.find(".add-photo-small").hide();
						self.$el.find(".desc-add").html(descView.render().el);
						self.$el.find(".desc-add").show();
					});
				}
			});
			/*
				Alternate the comment line below corresponding to the fragment preferences.
			*/
			var container = document.createDocumentFragment();
			//var images = new App.Collections.SpuzikImagesCollection({ UserId: this.options.UserId });

			this.collection.fetch({
				success: function(){
					if(self.collection.length > 0){
						self.collection.each(function(model){
							var imageView = new App.Views.SpuzikImageView({ model:model, vent: self.options.vent, view: self.options.view});
							/*
								Alternate the comment line below corresponding to the fragment preferences.
							*/
							container.appendChild(imageView.render().el);
							//self.$el.find(".img-holder").append(imageView.render().el);
						}, this);
						self.$el.find(".img-holder").append(container);
					}else{
						self.$el.find(".img-holder-no").show();
					}
				},
				error: function(){
					alert("there was a problem getting the images.");
				}
			});

			/*var spuzikImageHolder = new Spuzik.Views.SpuzikImageHolderView({ collection: images});
			this.$el.find('.image-holder').html(spuzikImageHolder.render().el);*/

			return this;
		},
		events: {
			"click .add-photo-btn": "dropMenu"
		},
		dropMenu: function(){
			this.$el.find(".add-photo-small").slideDown();
		}
	});

	App.Views.SpuzikImageView = Backbone.View.extend({
		initialize: function(options){
			this.options = options;
		},
		render: function(){
			this.$el.html( _.template($("#tabMediaThumb").html(), this.model.toJSON() ) );
			return this;
		},
		events:{

		}
	});

	App.Models.SpuzikDescriptionUpdateModel = Backbone.Model.extend({
		idAttribute: "ImageId",
		initialize: function(options){
			this.options = options;
		},
		defaults: {
			ImageId: "",
			Description: ""
		},
		urlRoot: "endpt.php/media"
	});

	App.Views.SpuzikTabMediaDescription = Backbone.View.extend({
		initialize: function(options){
			_.bindAll(this,"successCallback","errorCallback");
			this.options = options;
		},
		render: function(){
			this.$el.html( _.template($("#tabMediaDescription").html(), { PhotoURL: this.model, ID: this.model.split(".")[0] }));
			return this;
		},
		events: {
			"click .desc-add-button": "add",
			"click .desc-skip": "skip"
		},
		add: function(){
			var id = this.$el.find(".desc-textarea").attr("img-id");
			var desc = this.$el.find(".desc-textarea").val();

			var updateModel = new App.Models.SpuzikDescriptionUpdateModel();

			updateModel.set({
				ImageId: id,
				Description: desc
			});

			updateModel.save(null, {
				success: this.successCallback,
				error: this.errorCallback
			});

		},
		skip: function(){
			this.options.vent.trigger("update-feed");
			this.remove();
		},
		successCallback: function(){
			this.options.vent.trigger("update-feed");
			this.remove();
		},
		errorCallback: function(){
			alert("error");
		}
	});

	App.Views.SpuzikTabMyTunesView = Backbone.View.extend({
		initialize: function(){

		},
		render: function(){
			this.$el.html( $("#tabMyTunesTemplate").html() );
			return this;
		}
	});

	App.Views.SpuzikTabLinkView = Backbone.View.extend({
		tagName: "tr",
		initialize: function(options){
			this.options = options;
		},
		events:{
			"click .tab-link-remove": "remove"
		},
		render: function(){
			this.$el.html( _.template( $("#tabLinkTemplate").html(), this.model.toJSON() ) );

			if(!this.options.view){
				this.$el.find(".tab-link-remove").remove();
			}

			return this;
		},
		remove: function(){
			this.options.vent.trigger("removeLink", this.model);
			this.removeView();
		},
		removeView: function(){
			this.$el.remove();
		}
	});

	App.Views.SpuzikTabLinksView = Backbone.View.extend({
		initialize: function(options){
			_.bindAll(this,"successCallback","errorCallback");
			this.options = options;

			this.collection = new App.Collections.SpuzikLinksCollection({ UserId: this.options.UserId });
		},
		render: function(){
			this.options.vent.on("removeLink", this.removeLink, this);
			this.$el.html( $("#tabLinkHolderTemplate").html() );


			if(!this.options.view){
				this.$el.find(".add-link-btn").remove();
			}

			this.collection.fetch({
				success: this.successCallback,
				error: this.errorCallback
			});

			return this;
		},
		events: {
			"click .link-save-btn": "add",
			"click .add-link-btn": "dropAdd",
			"click .cancel-link-btn": "closeAdd"
		},
		add: function(){
			//possibly refresh the entire fq object here and add it with the righ MEMId for deletion to work right.
			var self = this;
			this.collection.create({
				LinkId: "1",
				UserId: "1",
				Text: this.$el.find(".link-title").val(),
				Url: this.$el.find(".link-content").val()
			},{
				silent: true,
				wait:true,
				success: function(model, response){
					self.closeAdd();
					self.render();
				},error: function(){
					alert("error");
				}
			});
		},
		removeLink: function(model){
			this.collection.remove(model);
			model.destroy();
		},
		dropAdd: function(){
			this.$el.find(".add-link-btn").hide();
			this.$el.find(".add-link").slideDown();
		},
		closeAdd: function(){
			var self = this;
			this.$el.find(".add-link").slideUp("fast",function(){
				self.$el.find(".add-link-btn").show();
			});
		},
		successCallback: function(collection){
			var container = document.createDocumentFragment();
			var self = this;

			if(collection.length > 0){
				collection.each(function(model){
					var linkView = new App.Views.SpuzikTabLinkView({ model:model, vent: self.options.vent, view: self.options.view});
					container.appendChild(linkView.render().el);
				}, this);
				this.$el.find(".link-table").append(container);
			}else{
				this.$el.find(".no-links").show();
				// this returns for the additional plotting
			}
		},
		errorCallback: function(collection){
			alert("error");
		}
	});

	App.Views.SpuzikTabLiveView = Backbone.View.extend({
		initialize: function(){

		},
		render: function(){
			this.$el.html( $("#tabLiveTemplate").html() );
			return this;
		}
	});

	App.Views.SpuzikTabZoneOutView = Backbone.View.extend({
		initialize: function(){

		},
		render: function(){
			this.$el.html( $("#tabZoneOutTemplate").html() );
			return this;
		}
	});
}());