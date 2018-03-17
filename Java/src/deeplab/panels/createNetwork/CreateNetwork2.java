package deeplab.panels.createNetwork;


import deeplab.util.Util;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;


public class CreateNetwork2 extends Scene {
	
	
	public static final int ACTIVATIONS_SIGMOID = 0x0;
	public static final int ACTIVATIONS_TANH = 0x1;
	public static final int ACTIVATIONS_RELU = 0x2;
	public static final int ACTIVATIONS_SOFTMAX = 0x3;
	
	// Component Lists for every Hidden Layer
	private Label[] labels_LayerNumber;
	private ToggleGroup[] toggleGroups;
	private RadioButton[] radioButtons_FullyConnected, radioButtons_Convolutional, radioButtons_Residual;
	private CheckBox[] checkBoxes_Pooling, checkBoxes_Padding;
	private ComboBox<String>[] comboBoxes_Activations;
	// Buttons
	private Button button_Back, button_Next;
	
	
	public CreateNetwork2( VBox root,int hiddenLayers ) {
		super( root );
		Util.addStylesheet(this);
		root.setPadding( new Insets( 5 ) );
		root.setSpacing( 10 );
		
		
		// Component Lists Initialization
		labels_LayerNumber = new Label[hiddenLayers];
		toggleGroups = new ToggleGroup[hiddenLayers];
		radioButtons_FullyConnected = new RadioButton[hiddenLayers];
		radioButtons_Convolutional = new RadioButton[hiddenLayers];
		radioButtons_Residual = new RadioButton[hiddenLayers];
		checkBoxes_Pooling = new CheckBox[hiddenLayers];
		checkBoxes_Padding = new CheckBox[hiddenLayers];
		comboBoxes_Activations = new ComboBox[hiddenLayers];
		
		
		// Create Hidden Layer Components
		VBox layout_HiddenLayerComponents = new VBox( 5 );
		for( int i = 0; i < hiddenLayers; i++ ) {
			HBox layout_OneHiddenLayer = new HBox( 10 );
			layout_OneHiddenLayer.setAlignment( Pos.CENTER );
			labels_LayerNumber[i] = new Label( "Hidden Layer No "+i );
			
			// Temp Variables to work around Javas collection limitations
			CheckBox pooling = new CheckBox( "Pooling" );
			CheckBox padding = new CheckBox( "Padding" );
			
			VBox layout_HiddenLayer_type = new VBox( 5 );
			toggleGroups[i] = new ToggleGroup();
			radioButtons_FullyConnected[i] = new RadioButton( "Fully connected" );
			radioButtons_FullyConnected[i].setUserData( "fully connected" );
			radioButtons_FullyConnected[i].setToggleGroup( toggleGroups[i] );
			radioButtons_FullyConnected[i].setSelected( true );
			radioButtons_Convolutional[i] = new RadioButton( "Convolutional" );
			radioButtons_Convolutional[i].setUserData( "convolutional" );
			radioButtons_Convolutional[i].setToggleGroup( toggleGroups[i] );
			radioButtons_Residual[i] = new RadioButton( "Residual" );
			radioButtons_Residual[i].setUserData( "residual" );
			radioButtons_Residual[i].setToggleGroup( toggleGroups[i] );
			toggleGroups[i].selectedToggleProperty().addListener( new ChangeListener<Toggle>() {
				@Override
				public void changed( ObservableValue<? extends Toggle> observable,Toggle oldValue,Toggle newValue ) {
					if( newValue.getUserData().equals( "convolutional" ) ) {
						pooling.setDisable( false );
						padding.setDisable( false );
					} else {
						pooling.setDisable( true );
						padding.setDisable( true );
					}
				}
			} );
			layout_HiddenLayer_type.getChildren().addAll( radioButtons_FullyConnected[i],radioButtons_Convolutional[i],radioButtons_Residual[i] );
			
			VBox layout_HiddenLayer_options = new VBox( 5 );
			checkBoxes_Pooling[i] = pooling;
			checkBoxes_Pooling[i].setDisable( true );
			checkBoxes_Padding[i] = padding;
			checkBoxes_Padding[i].setDisable( true );
			if( i == hiddenLayers-1 )
				comboBoxes_Activations[i] = new ComboBox<>( FXCollections.observableArrayList( "Sigmoid","tanh","Relu","Softmax" ) );
			else
				comboBoxes_Activations[i] = new ComboBox<>( FXCollections.observableArrayList( "Sigmoid","tanh","Relu" ) );
			layout_HiddenLayer_options.getChildren().addAll( checkBoxes_Pooling[i],checkBoxes_Padding[i],comboBoxes_Activations[i] );
			
			layout_OneHiddenLayer.getChildren().addAll( labels_LayerNumber[i],layout_HiddenLayer_type,layout_HiddenLayer_options );
			
			
			Separator separator = new Separator();
			layout_HiddenLayerComponents.getChildren().addAll( layout_OneHiddenLayer,separator );
		}
		
		
		// Buttons
		HBox layout_Buttons = new HBox( 5 );
		layout_Buttons.setAlignment( Pos.BASELINE_RIGHT );
		button_Back = new Button( "Back" );
		button_Next = new Button( "Next" );
		layout_Buttons.getChildren().addAll( button_Back,button_Next );
		
		
		root.getChildren().addAll( layout_HiddenLayerComponents,layout_Buttons );
	}
	
	
	public void addButtonBackListener( EventHandler eventHandler ) {
		button_Back.setOnAction( e -> eventHandler.handle( e ) );
	}
	
	public void addButtonNextListener( EventHandler eventHandler ) {
		button_Next.setOnAction( e -> eventHandler.handle( e ) );
	}
	
	
	public ToggleGroup[] getToggleGroups() {
		return toggleGroups;
	}
	
	public CheckBox[] getCheckBoxes_Pooling() {
		return checkBoxes_Pooling;
	}
	
	public CheckBox[] getCheckBoxes_Padding() {
		return checkBoxes_Padding;
	}
	
	public ComboBox<String>[] getComboBoxes_Activations() {
		return comboBoxes_Activations;
	}
	
	
}
