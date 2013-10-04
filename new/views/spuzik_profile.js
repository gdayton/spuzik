(function(){
	"use strict";
	window.App = window.App || {Routers: {}, Collections: {}, Models: {}, Views: {}};
	App.Views.SpuzikProfileView = Backbone.View.extend({
		initialize: function(){
			_.bindAll(this,"successCallback","errorCallback");
		},
		render: function(){
			var view = this;

			/*
				Sets up tiny user info
			*/
			/*var userInfo = new App.Models.SpuzikUserModel({ id: this.model[1] });
			userInfo.fetch();
			var infoView = new App.Views.SpuzikInfoView({ model: userInfo });
			this.$el.find("#profile").html(infoView.render().el);*/

			this.userInfo = new App.Models.SpuzikUserModel({ id: this.model[1] });
			this.userInfo.fetch({
				success: this.successCallback,
				error: this.errorCallback
			});

			//this.miniData.call(this);

			//var infoView = new App.Views.SpuzikInfoView({ model: this.userInfo });
			//this.$el.find("#profile").html(infoView.render().el);


			var secondView = new App.Views.SpuzikHeaderView();
			this.$el.html(secondView.render().el);
			this.$el.append( $("#profileTemplate").html() );

			/*
				DATA INSERT - LINEUP
			*/
			var lineupCollection = new App.Collections.SpuzikLineupCollection({ UserId:this.model[1], vent: this.model[3] });
			/*
				Sets up lineup
			*/
			var self = this;
			lineupCollection.fetch({
				beforeSend: function(){
					view.$el.find(".lineup").html($("#lineupLoadingTemplate").html());
				},
				/*complete: function(){
					view.$el.find(".lineup").html(lineupView.render().el);
				},*/
				success: function(){
					var lineupView = new App.Views.SpuzikLineupView({ collection: lineupCollection, view: self.model[2], vent: self.model[3] });

					//TODO check if user is logged in! matters!
					if(self.model[2]){

						var lineupAddView = new App.Views.SpuzikAddLineupView({ vent: self.model[3] });
						view.$el.find(".lineup").html(lineupAddView.render().el);
					}

					view.$el.find(".lineup").append(lineupView.render().el);
					//used for making stuff draggable
					/*$(".lineup-container").sortable({
						revert:true,
						axis:"y",
						stop: function(event, ui) {
							ui.item.trigger('drop', $(this).attr("id"));
						}
					});*/
					view.$el.find(".lineupLoading").hide();
				},
				error: function(){
					if(self.model[2]){
						var lineupAddView = new App.Views.SpuzikAddLineupView({ vent: self.model[3] });
						view.$el.find(".lineup").html(lineupAddView.render().el);
					}
					view.$el.find(".lineup").append($("#lineupErrorTemplate").html());
				}
			});

			var topView = new App.Views.SpuzikTopView({ model: this.model[0], vent: self.model[3], view: self.model[2], UserId: self.model[1] });
			this.$el.find("#sli-tab").html(topView.render().el);

			return this;
		},
		events: {

		},
		successCallback: function(model){
			var infoView = new App.Views.SpuzikInfoView({ model: model });
			this.$el.find("#profile").html(infoView.render().el);
		},
		errorCallback: function(model){
			alert("error");
		}
	});

	App.Views.SpuzikInfoView = Backbone.View.extend({
		initialize: function(){

		},
		render: function(){
			this.$el.html( _.template($("#userInfoTemplate").html(), this.model.toJSON()) );
			return this;
		}
	});
}());