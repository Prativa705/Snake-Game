#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <deque>
#include <random>
#include <string>

const int CELL_SIZE = 20;
const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 20;
const int WINDOW_WIDTH = CELL_SIZE * GRID_WIDTH;
const int WINDOW_HEIGHT = CELL_SIZE * GRID_HEIGHT;

enum Direction { Up, Down, Left, Right };

struct SnakeGame {
    std::deque<sf::Vector2i> snake;
    sf::Vector2i food;
    Direction dir = Right;
    bool gameOver = false;
    int score = 0;
    int highScore = 0;
    float moveDelay = 0.15f; // seconds
    float timer = 0.f;
    std::mt19937 rng{std::random_device{}()};
    sf::SoundBuffer eatBuffer, gameOverBuffer;
    sf::Sound eatSound, gameOverSound;
    sf::Font font;
    sf::Text scoreText, gameOverText, restartText;

    SnakeGame() {
        reset();
        eatBuffer.loadFromFile("eat.wav");
        gameOverBuffer.loadFromFile("gameover.wav");
        eatSound.setBuffer(eatBuffer);
        gameOverSound.setBuffer(gameOverBuffer);
        font.loadFromFile("arial.ttf");
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(5, 0);
        gameOverText.setFont(font);
        gameOverText.setCharacterSize(36);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setString("Game Over!");
        gameOverText.setPosition(WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 - 60);
        restartText.setFont(font);
        restartText.setCharacterSize(20);
        restartText.setFillColor(sf::Color::Yellow);
        restartText.setString("Press Enter to Restart");
        restartText.setPosition(WINDOW_WIDTH/2 - 110, WINDOW_HEIGHT/2);
    }

    void reset() {
        snake.clear();
        snake.push_back({GRID_WIDTH/2, GRID_HEIGHT/2});
        dir = Right;
        gameOver = false;
        score = 0;
        moveDelay = 0.15f;
        placeFood();
    }

    void placeFood() {
        std::uniform_int_distribution<int> distX(0, GRID_WIDTH-1);
        std::uniform_int_distribution<int> distY(0, GRID_HEIGHT-1);
        while (true) {
            food = {distX(rng), distY(rng)};
            bool onSnake = false;
            for (auto& s : snake) if (s == food) onSnake = true;
            if (!onSnake) break;
        }
    }

    void update(float dt) {
        if (gameOver) return;
        timer += dt;
        if (timer >= moveDelay) {
            timer = 0.f;
            move();
        }
    }

    void move() {
        sf::Vector2i head = snake.front();
        switch (dir) {
            case Up: head.y -= 1; break;
            case Down: head.y += 1; break;
            case Left: head.x -= 1; break;
            case Right: head.x += 1; break;
        }
        // Check collision with wall
        if (head.x < 0 || head.x >= GRID_WIDTH || head.y < 0 || head.y >= GRID_HEIGHT) {
            onGameOver();
            return;
        }
        // Check collision with self
        for (auto& s : snake) {
            if (s == head) {
                onGameOver();
                return;
            }
        }
        // Move snake
        snake.push_front(head);
        if (head == food) {
            eatSound.play();
            score++;
            if (score > highScore) highScore = score;
            // Increase speed every 3 points
            if (score % 3 == 0 && moveDelay > 0.05f) moveDelay -= 0.015f;
            placeFood();
        } else {
            snake.pop_back();
        }
    }

    void onGameOver() {
        gameOver = true;
        gameOverSound.play();
    }

    void handleInput(sf::Keyboard::Key key) {
        if (gameOver) {
            if (key == sf::Keyboard::Enter) {
                reset();
            }
            return;
        }
        if ((key == sf::Keyboard::Up || key == sf::Keyboard::W) && dir != Down) dir = Up;
        else if ((key == sf::Keyboard::Down || key == sf::Keyboard::S) && dir != Up) dir = Down;
        else if ((key == sf::Keyboard::Left || key == sf::Keyboard::A) && dir != Right) dir = Left;
        else if ((key == sf::Keyboard::Right || key == sf::Keyboard::D) && dir != Left) dir = Right;
    }

    void draw(sf::RenderWindow& window) {
        // Background
        window.clear(sf::Color(30, 30, 30));
        // Draw food
        sf::RectangleShape foodRect({(float)CELL_SIZE, (float)CELL_SIZE});
        foodRect.setFillColor(sf::Color::Red);
        foodRect.setPosition(food.x * CELL_SIZE, food.y * CELL_SIZE);
        window.draw(foodRect);
        // Draw snake
        for (size_t i = 0; i < snake.size(); ++i) {
            sf::RectangleShape rect({(float)CELL_SIZE-2, (float)CELL_SIZE-2});
            rect.setPosition(snake[i].x * CELL_SIZE+1, snake[i].y * CELL_SIZE+1);
            if (i == 0) rect.setFillColor(sf::Color::Green);
            else rect.setFillColor(sf::Color(0, 180, 0));
            window.draw(rect);
        }
        // Draw score
        scoreText.setString("Score: " + std::to_string(score) + "  High: " + std::to_string(highScore));
        window.draw(scoreText);
        // Draw game over
        if (gameOver) {
            window.draw(gameOverText);
            window.draw(restartText);
        }
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Snake Game");
    window.setFramerateLimit(60);
    SnakeGame game;
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                game.handleInput(event.key.code);
        }
        float dt = clock.restart().asSeconds();
        game.update(dt);
        game.draw(window);
        window.display();
    }
    return 0;
}