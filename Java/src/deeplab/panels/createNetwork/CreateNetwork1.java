package deeplab.panels.createNetwork;


import deeplab.util.Util;
import javafx.collections.FXCollections;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;


public class CreateNetwork1 extends Scene {
	
	
	public static final int COST_FUNCTION_MSE = 0x0;
	public static final int COST_FUNCTION_CROSS_ENTROPY = 0x1;
	
	// Input Neurons
	private Label label_InputNeurons, label_Channels, label_Rows, label_Columns;
	private Spinner<Integer> spinner_Channels, spinner_Rows, spinner_Columns;
	// Hidden Layers
	private Label label_HiddenLayers;
	private Spinner<Integer> spinner_HiddenLayers;
	// Output Neurons
	private Label label_OutputNeurons;
	private Spinner<Integer> spinner_OutputNeurons;
	// Cost Function
	private Label label_CostFunction;
	private ComboBox<String> comboBox_CostFunction;
	// Buttons
	private Button button_Next;
	
	
	public CreateNetwork1( VBox root ) {
		super( root );
		Util.addStylesheet(this);
		root.setPadding( new Insets( 5 ) );
		root.setSpacing( 10 );
		
		
		// Input Neurons
		HBox layout_InputNeurons = new HBox( 5 );
		label_InputNeurons = new Label( "Input Neurons" );
		label_InputNeurons.setPrefWidth( 100 );
		
		VBox layout_InputNeurons_channels = new VBox( 5 );
		layout_InputNeurons_channels.setAlignment( Pos.BASELINE_CENTER );
		spinner_Channels = new Spinner<>( 1,99,1 );
		spinner_Channels.setEditable( true );
		spinner_Channels.setPrefWidth( 55 );
		label_Channels = new Label( "Channels" );
		label_Channels.setFont( new Font( 11 ) );
		layout_InputNeurons_channels.getChildren().addAll( spinner_Channels,label_Channels );
		
		VBox layout_InputNeurons_rows = new VBox( 5 );
		layout_InputNeurons_rows.setAlignment( Pos.BASELINE_CENTER );
		spinner_Rows = new Spinner<>( 1,99,1 );
		spinner_Rows.setEditable( true );
		spinner_Rows.setPrefWidth( 55 );
		label_Rows = new Label( "Rows" );
		label_Rows.setFont( new Font( 11 ) );
		layout_InputNeurons_rows.getChildren().addAll( spinner_Rows,label_Rows );
		
		VBox layout_InputNeurons_columns = new VBox( 5 );
		layout_InputNeurons_columns.setAlignment( Pos.BASELINE_CENTER );
		spinner_Columns = new Spinner<>( 1,99,1 );
		spinner_Columns.setEditable( true );
		spinner_Columns.setPrefWidth( 55 );
		label_Columns = new Label( "Columns" );
		label_Columns.setFont( new Font( 11 ) );
		layout_InputNeurons_columns.getChildren().addAll( spinner_Columns,label_Columns );
		
		layout_InputNeurons.getChildren().addAll( label_InputNeurons,layout_InputNeurons_channels,layout_InputNeurons_rows,layout_InputNeurons_columns );
		
		
		// Hidden Layers
		HBox layout_HiddenLayers = new HBox( 5 );
		label_HiddenLayers = new Label( "Hidden Layers" );
		label_HiddenLayers.setPrefWidth( 100 );
		spinner_HiddenLayers = new Spinner<>( 1,99,1 );
		spinner_HiddenLayers.setPrefWidth( 55 );
		layout_HiddenLayers.getChildren().addAll( label_HiddenLayers,spinner_HiddenLayers );
		
		
		// Output Neurons
		HBox layout_OutputNeurons = new HBox( 5 );
		label_OutputNeurons = new Label( "Output Neurons" );
		label_OutputNeurons.setPrefWidth( 100 );
		spinner_OutputNeurons = new Spinner<>( 1,99,1 );
		spinner_OutputNeurons.setPrefWidth( 55 );
		layout_OutputNeurons.getChildren().addAll( label_OutputNeurons,spinner_OutputNeurons );
		
		
		// Cost Function
		HBox layout_CostFunction = new HBox( 5 );
		label_CostFunction = new Label( "Cost Function" );
		label_CostFunction.setPrefWidth( 100 );
		comboBox_CostFunction = new ComboBox<>( FXCollections.observableArrayList( "MSE","Cross-Entropy" ) );
		comboBox_CostFunction.setPrefWidth( 175 );
		layout_CostFunction.getChildren().addAll( label_CostFunction,comboBox_CostFunction );
		
		
		// Buttons
		HBox layout_Buttons = new HBox( 5 );
		layout_Buttons.setAlignment( Pos.BASELINE_RIGHT );
		button_Next = new Button( "Next" );
		layout_Buttons.getChildren().addAll( button_Next );
		
		
		Separator separator = new Separator(  );
		root.getChildren().addAll( layout_InputNeurons,layout_HiddenLayers,layout_OutputNeurons,layout_CostFunction,separator,layout_Buttons );
	}
	
	
	public void addButtonNextListener( EventHandler eventHandler ) {
		button_Next.setOnAction( e -> eventHandler.handle( e ) );
	}
	
	
	public int getChannelsValue() {
		return spinner_Channels.getValue();
	}
	
	public int getRowsValue() {
		return spinner_Rows.getValue();
	}
	
	public int getColumnsValue() {
		return spinner_Columns.getValue();
	}
	
	public int getHiddenLayersValue() {
		return spinner_HiddenLayers.getValue();
	}
	
	public int getCostFunctionValue() {
		if(comboBox_CostFunction.getValue()==null)
			return -1;
		else if( comboBox_CostFunction.getValue().equals( "MSE" ) )
			return COST_FUNCTION_MSE;
		else if( comboBox_CostFunction.getValue().equals( "Cross-Entropy" ) )
			return COST_FUNCTION_CROSS_ENTROPY;
		else
			return -1;
	}
	
	
}
