/* 
	Simple Task Bar
	Copyright Francois Thirioux 2020
	GitHub contributors: @fthx (original extension), @leleat (more settings, settings UI)
	License GPL v3
*/

const Lang = imports.lang;
const St = imports.gi.St;
const Main = imports.ui.main;
const Util = imports.misc.util;
const Meta = imports.gi.Meta;
const Shell = imports.gi.Shell;
const Clutter = imports.gi.Clutter;
const AppMenu = Main.panel.statusArea.appMenu;
const PopupMenu = imports.ui.popupMenu;
const GLib = imports.gi.GLib;
const Gio = imports.gi.Gio;
const Me = imports.misc.extensionUtils.getCurrentExtension();
const PanelBox = Main.layoutManager.panelBox;
const SessionMode = imports.ui.sessionMode;

// translation needed to restore Places Menu label when disable extension
const Gettext = imports.gettext.domain('gnome-shell-extensions');
const _ = Gettext.gettext;
const N_ = x => x;


const WindowList = new Lang.Class({
	Name: 'WindowList.WindowList',
	
	// create the task bar container and signals
	_init: function(){
		this.signals_array = [];

		this._set_Activities_visibility(false);
	
		this.apps_menu = new St.BoxLayout({});
		this.actor = this.apps_menu;
        this._updateMenu();
		this._restacked = global.display.connect('restacked', Lang.bind(this, this._updateMenu));
		this._window_change_monitor = global.display.connect('window-left-monitor', Lang.bind(this, this._updateMenu));
		this._workspace_changed = global.workspace_manager.connect('active-workspace-changed', Lang.bind(this, this._updateMenu));
		this._workspace_number_changed = global.workspace_manager.connect('notify::n-workspaces', Lang.bind(this, this._updateMenu));
	},

	// destroy the task bar
	_destroy: function() {

		this._set_Activities_visibility(true);

		// disconnect all signals
		global.display.disconnect(this._restacked);
		global.display.disconnect(this._window_change_monitor);
		global.workspace_manager.disconnect(this._workspace_changed);
		global.workspace_manager.disconnect(this._workspace_number_changed);
		
		// destroy task bar container
		this.apps_menu.destroy();
	},
	
	// hide Activities button
	_set_Activities_visibility: function(is_visible) {
		if (is_visible) {
			let activities_indicator = Main.panel.statusArea['activities'];
			if (activities_indicator && !Main.sessionMode.isLocked) {
				activities_indicator.container.show();
			}
			Main.panel.statusArea.appMenu.disconnect(signalShow);
    		Main.panel.statusArea.appMenu.show();
    		
    		Main.overview.dash.show();
		} else {
			let activities_indicator = Main.panel.statusArea['activities'];
			if (activities_indicator) {
				activities_indicator.container.hide();
			}
			signalShow=Main.panel.statusArea.appMenu.connect("show",function () {
        		Main.panel.statusArea.appMenu.hide();});
    		Main.panel.statusArea.appMenu.hide();
    		
    		
    		Main.overview.dash.hide();
		}
	},
	
	// update the task bar
    _updateMenu: function() {   
    	// destroy old task bar 	
    	this.apps_menu.destroy_all_children();

    	
    	// track windows and get the number of workspaces
        this.tracker = Shell.WindowTracker.get_default();
        this.workspaces_count = global.workspace_manager.get_n_workspaces();
		
		// do this for all existing workspaces
		this.last_workspace = this.workspaces_count - 1
		
        for (let workspace_index = 0; workspace_index < this.last_workspace; ++workspace_index) {
        
            let metaWorkspace = global.workspace_manager.get_workspace_by_index(workspace_index);
            this.windows = metaWorkspace.list_windows().sort(this._sortWindows);
           
            
			// create all normal windows icons and buttons
            for ( let i = 0; i < this.windows.length; ++i ) {
	            let metaWindow = this.windows[i];
	            let box = new St.Bin({visible: true, 
        						reactive: true, can_focus: true, track_hover: false});
	            box.window = this.windows[i];
	            box.app = this.tracker.get_window_app(box.window);
                box.connect('button-press-event', Lang.bind(this, function() {
                							this._activateWindow(metaWorkspace, metaWindow); } ));
				box.icon = box.app.create_icon_texture(20);
                
               	box.set_child(box.icon);

		        let iconEffect = new Clutter.DesaturateEffect();             	
               	if (!metaWindow.has_focus()) {
               		box.icon.add_effect(iconEffect);
               	}
		        if (global.workspace_manager.get_active_workspace() !== metaWorkspace) {
					let briEffect = new Clutter.BrightnessContrastEffect({});
					briEffect.set_brightness(-0.5);
					box.icon.add_effect(briEffect);
				}
               	
                this.apps_menu.add_actor(box);
            };
        };
    },

	// windows list sort function by window id
    _sortWindows: function(w1, w2) {
    	return w1.get_id() - w2.get_id();
    },
    
    // activate workspace ws
    _activateWorkspace: function(ws) {
		if (global.workspace_manager.get_active_workspace() === ws) {
			Main.overview.toggle();
		}
		else {
			Main.overview.show();
		};
		ws.activate(global.get_current_time());
    },

	// switch to workspace ws and activate window w
    _activateWindow: function(ws, w) {
        if (global.workspace_manager.get_active_workspace() === ws && w.has_focus() 
        												&& !(Main.overview.visible)) {
       		w.minimize();
       	}
        else {	
        	//w.unminimize();
			//w.unshade(global.get_current_time());
			w.activate(global.get_current_time());
		};
		Main.overview.hide();
		if (!(w.is_on_all_workspaces())) { ws.activate(global.get_current_time()); };
    }

});

let windowlist;

//https://github.com/Thoma5/gnome-shell-extension-bottompanel/blob/master/extension.js
function _toTop() {
   let monitor = Main.layoutManager.primaryMonitor;  
   PanelBox.set_pivot_point(0,0);
   PanelBox.set_position(0,0);
}
function _toBottom() {
    let monitor = Main.layoutManager.primaryMonitor;
    PanelBox.set_pivot_point(0,(-1)*(monitor.height-PanelBox.height));
    PanelBox.set_position(0,(monitor.height-PanelBox.height));
}










function clockright() {
    // do nothing if the clock isn't centred in this mode
    if ( Main.sessionMode.panel.center.indexOf('dateMenu') == -1 ) {
        return;
    }

    let centerBox = Main.panel._centerBox;
    let rightBox = Main.panel._rightBox;
    let dateMenu = Main.panel.statusArea['dateMenu'];
    let children = centerBox.get_children();

    // only move the clock if it's in the centre box
    if ( children.indexOf(dateMenu.container) != -1 ) {
        centerBox.remove_actor(dateMenu.container);

        children = rightBox.get_children();
        rightBox.insert_child_at_index(dateMenu.container, children.length);
   }
}

function clockback() {
    // do nothing if the clock isn't centred in this mode
    if ( Main.sessionMode.panel.center.indexOf('dateMenu') == -1 ) {
        return;
    }

    let centerBox = Main.panel._centerBox;
    let rightBox = Main.panel._rightBox;
    let dateMenu = Main.panel.statusArea['dateMenu'];
    let children = rightBox.get_children();

    // only move the clock back if it's in the right box
    if ( children.indexOf(dateMenu.container) != -1 ) {
        rightBox.remove_actor(dateMenu.container);
        centerBox.add_actor(dateMenu.container);
    }
}









function init() {
}

function enable() {
    // activate and display task bar in the panel
	windowlist = new WindowList;
    let position = 1;
    if ('places-menu' in Main.panel.statusArea)
        position++;
    Main.panel._leftBox.insert_child_at_index(windowlist.actor, position);

	// hide icon before the AppMenu label
	AppMenu._iconBox.hide();
	
	
	MonitorsChangedListener = Main.layoutManager.connect("monitors-changed", _toBottom);
    HeightNotifyListener = PanelBox.connect("notify::height", _toBottom);
	_toBottom();
	clockright();

}

function disable() {
	// destroy task bar
	windowlist._destroy();

	// restore default AppMenu label
	AppMenu._iconBox.show();
	
	
	if(HeightNotifyListener !== null) {
        PanelBox.disconnect(HeightNotifyListener);
    }
    if(MonitorsChangedListener !== null) {
        Main.layoutManager.disconnect(MonitorsChangedListener);
    }
	_toTop();
	clockback();
}
