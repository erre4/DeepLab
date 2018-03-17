package deeplab.stages;


import deeplab.panels.createNetwork.CreateNetwork1;
import deeplab.panels.createNetwork.CreateNetwork2;
import deeplab.panels.createNetwork.CreateNetwork3;
import deeplab.studio.DeepLabStudio;
import javafx.event.Event;
import javafx.scene.control.ComboBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;


public class CreateNetworkDialog extends Stage {
	
	
	public CreateNetwork1 panel_CreateNetwork1;
	public CreateNetwork2 panel_CreateNetwork2;
	public CreateNetwork3 panel_CreateNetwork3;
	
	
	public CreateNetworkDialog( ) {
		super();
		super.initOwner( DeepLabStudio.getPrimaryStage());
		super.setTitle( "Create Network 1/3" );
		super.setResizable( false );
		
		
		createPanel1();
		enterPanel1();
		super.showAndWait();
	}
	
	
	private void createPanel1() {
		panel_CreateNetwork1 = new CreateNetwork1( new VBox(  ) );
		panel_CreateNetwork1.addButtonNextListener( e->panel1_button_Next_pressed( e ) );
	}
	
	public void createPanel2() {
		panel_CreateNetwork2 = new CreateNetwork2( new VBox(  ),panel_CreateNetwork1.getHiddenLayersValue() );
		panel_CreateNetwork2.addButtonBackListener(e->panel2_button_Back_pressed( e ));
		panel_CreateNetwork2.addButtonNextListener(e->panel2_button_Next_pressed( e ));
	}
	
	public void createPanel3() {
		panel_CreateNetwork3 = new CreateNetwork3( new VBox(  ),panel_CreateNetwork1.getHiddenLayersValue(),this );
		panel_CreateNetwork3.addButtonBackListener(e->panel3_button_Back_pressed( e ));
		panel_CreateNetwork3.addButtonFinishListener(e->panel3_button_Finish_pressed( e ));
	}
	
	public void enterPanel1() {
		super.setTitle( "Create Network 1/3" );
		super.setScene( panel_CreateNetwork1 );
		super.sizeToScene();
	}
	
	public void enterPanel2() {
		createPanel2( );
		super.setTitle( "Create Network 2/3" );
		super.setScene( panel_CreateNetwork2 );
		super.sizeToScene();
	}
	
	public void enterPanel3() {
		createPanel3( );
		super.setTitle( "Create Network 3/3" );
		super.setScene( panel_CreateNetwork3 );
		super.sizeToScene();
	}
	
	
	private void panel1_button_Next_pressed( Event e ) {
		if(panel_CreateNetwork1.getCostFunctionValue()!=-1)
			enterPanel2();
	}
	
	private void panel2_button_Back_pressed( Event e ) {
		super.setTitle( "Create Network 1/3" );
		super.setScene( panel_CreateNetwork1 );
	}
	
	private void panel2_button_Next_pressed( Event e ) {
		String boxValue;
		for( ComboBox<String> comboBox : panel_CreateNetwork2.getComboBoxes_Activations() ) {
			boxValue = comboBox.getValue();
			if(boxValue==null)
				return;
		}
		enterPanel3();
	}
	
	private void panel3_button_Back_pressed( Event e ) {
		super.setTitle( "Create Network 2/3" );
		super.setScene( panel_CreateNetwork2 );
	}
	
	private void panel3_button_Finish_pressed( Event e ) {
	
	}
	
	
}
