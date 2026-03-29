package perfectly_moving_square;

import javafx.scene.input.KeyEvent;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

public abstract class Drawable {
    protected GraphicsContext gc;
    protected int canvasWidth = 800;
    protected int canvasHeight = 600;
    protected double x = canvasWidth / 2;
    protected double y = canvasHeight / 2;
    protected int width = 50;
    protected int height = 50;
    protected Color color = Color.PURPLE;
    private final double defaultMoveLeap = 1;
    private double moveLeap = defaultMoveLeap;
    private double diagonalMoveLeap = (defaultMoveLeap * Math.sqrt(2)) / 2;
    public Direction directionX = Direction.NULL;
    public Direction directionY = Direction.NULL;
    public void draw() {
        updatePosition();
        gc.setFill(color);
        gc.fillRect(x - width / 2, y - height / 2, width, height);
    }
    protected Drawable(GraphicsContext _gc) {
        gc = _gc;
    }
    protected void init(double _x, double _y, int _width, int _height, Color _color, int _canvasWidth, int _canvasHeight, Direction _directionX, Direction _directionY) {
        x = _x;
        y = _y;
        width = _width;
        height = _height;
        color = _color;
        canvasWidth = _canvasWidth;
        canvasHeight = _canvasHeight;
        directionX = _directionX;
        directionY = _directionY;
    }
    protected void updatePosition() {
        switch(directionX) {
            case LEFT:
                x -= moveLeap;
                break;
            case RIGHT:
                x += moveLeap;
                break;
            case NULL:
                break;
        }
        switch(directionY) {
            case UP:
                y -= moveLeap;
                break;
            case DOWN:
                y += moveLeap;
                break;
            case NULL:
                break;
        }
    }
    protected Direction lastDirectionX = Direction.NULL;
    protected Direction lastDirectionY = Direction.NULL;
    public void inputToMovementPressed(KeyEvent event) {
        boolean dontLogNewDirectionX = false;
        boolean dontLogNewDirectionY = false;
        switch(event.getCode()) {
            case LEFT:
                if(lastDirectionY != Direction.NULL) {
                    moveLeap = diagonalMoveLeap;
                }
                directionX = Direction.LEFT;
                if(lastDirectionX == Direction.RIGHT) {
                    dontLogNewDirectionX = true;
                }
                break;
            case RIGHT:
                if(lastDirectionY != Direction.NULL) {
                    moveLeap = diagonalMoveLeap;
                }
                directionX = Direction.RIGHT;
                if(lastDirectionX == Direction.LEFT) {
                    dontLogNewDirectionX = true;
                }
                break;
            case UP:
                if(lastDirectionX != Direction.NULL) {
                    moveLeap = diagonalMoveLeap;
                }
                directionY = Direction.UP;
                if(lastDirectionY == Direction.DOWN) {
                    dontLogNewDirectionY = true;
                }
                break;
            case DOWN:
                if(lastDirectionX != Direction.NULL) {
                    moveLeap = diagonalMoveLeap;
                }
                directionY = Direction.DOWN;
                if(lastDirectionY == Direction.UP) {
                    dontLogNewDirectionY = true;
                }
                break;
        }
        if(dontLogNewDirectionX) {
            return;
        }
        if(dontLogNewDirectionY) {
            return;
        }
        lastDirectionX = directionX;
        lastDirectionY = directionY;
    }
    public void inputToMovementReleased(KeyEvent event) {
        moveLeap = defaultMoveLeap;
        switch(event.getCode()) {
            case LEFT:
                if(lastDirectionX == Direction.RIGHT) {
                    directionX = Direction.RIGHT;
                    break;
                }
                if(directionX == Direction.RIGHT && lastDirectionX == Direction.LEFT) {
                    break;
                }
                directionX = Direction.NULL;
                break;
            case RIGHT:
                if(lastDirectionX == Direction.LEFT) {
                    directionX = Direction.LEFT;
                    break;
                }
                if(directionX == Direction.LEFT && lastDirectionX == Direction.RIGHT) {
                    break;
                }
                directionX = Direction.NULL;
                break;
            case UP:
                if(lastDirectionY == Direction.DOWN) {
                    directionY = Direction.DOWN;
                    break;
                }
                if(directionY == Direction.DOWN && lastDirectionY == Direction.UP) {
                    break;
                }
                directionY = Direction.NULL;
                break;
            case DOWN:
                if(lastDirectionY == Direction.UP) {
                    directionY = Direction.UP;
                    break;
                }
                if(directionY == Direction.UP && lastDirectionY == Direction.DOWN) {
                    break;
                }
                directionY = Direction.NULL;
                break;
        }
        lastDirectionX = directionX;
        lastDirectionY = directionY;
    }   
}
