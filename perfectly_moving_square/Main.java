package perfectly_moving_square;

import javafx.event.Event;
import javafx.event.ActionEvent;
import javafx.scene.Group;
import javafx.animation.KeyValue;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.application.Application;
import javafx.beans.value.WritableValue;    
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.input.KeyEvent;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.stage.Stage;
import javafx.util.Duration;
import javafx.event.EventHandler;

public class Main extends Application {
    private static final int SCENE_WIDTH = 800;
    private static final int SCENE_HEIGHT = 600;
    private static final int CANVAS_WIDTH = SCENE_WIDTH;
    private static final int CANVAS_HEIGHT = SCENE_HEIGHT;
    private static final Group group = new Group();
    private static final Canvas canvas = new Canvas(CANVAS_WIDTH, CANVAS_HEIGHT);
    private static final GraphicsContext gc = canvas.getGraphicsContext2D();
    public static void draw(Drawable... nodes) {
        for(var node : nodes) {
            node.draw();
        }
    }
    public static void movePressed(KeyEvent event, Drawable... nodes) {
        for(var node : nodes) {
            node.inputToMovementPressed(event);
        }
    }
    public static void moveReleased(KeyEvent event, Drawable... nodes) {
        for(var node : nodes) {
            node.inputToMovementReleased(event);
        }
    }
    public static void clear() {
        gc.clearRect(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);
    }
    @Override
    public void start(Stage stage) {

        Player player = new Player(gc);

        stage.addEventHandler(KeyEvent.KEY_PRESSED, (event) -> {
            movePressed(event, player);
        });

        stage.addEventHandler(KeyEvent.KEY_RELEASED, (event) -> {
            moveReleased(event, player);
        });

        Thread gameLoop = Thread.ofVirtual().start(() -> {
            while(true) {
                clear();
                draw(player);
                try {
                    Thread.sleep(30);
                } catch(InterruptedException e) {
                    break;
                }
            }
        });

        group.getChildren().add(canvas);
        stage.setScene(new Scene(group, SCENE_WIDTH, SCENE_HEIGHT));
        stage.show();
    }
    public static void main(String[] args) {
        launch();
    }
}
