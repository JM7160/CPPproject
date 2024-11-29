#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(1413, 768), "Culinary Class Wars");

    // ���� ��� �� ��ư ����
    sf::Texture startBackgroundTexture, buttonTexture;
    startBackgroundTexture.loadFromFile("StartBackground.png");
    buttonTexture.loadFromFile("startbutton.png");
    sf::Sprite background(startBackgroundTexture), button(buttonTexture);
    background.setScale(
        static_cast<float>(window.getSize().x) / startBackgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / startBackgroundTexture.getSize().y
    ); 
    button.setScale(0.34f, 0.34f);
    button.setPosition(18.0f, window.getSize().y - button.getGlobalBounds().height + 83.0f);

    // ��ȭ �ؽ�ó �� ��ư
    sf::Texture talk1Texture, talk2Texture, talk3Texture, talk4Texture, talk5Texture,
        talk6Texture, talk7Texture, talk8Texture, talk9Texture, mctalk2Texture, nextButtonTexture,
        image1Texture, image2Texture, baekTexture, basTexture;
    talk1Texture.loadFromFile("mctalk1.png");
    talk2Texture.loadFromFile("talk1.png");
    talk3Texture.loadFromFile("talk2.png");
    talk4Texture.loadFromFile("talk3.png");
    talk5Texture.loadFromFile("talk4.png");
    talk6Texture.loadFromFile("talk5.png");
    talk7Texture.loadFromFile("talk6.png");
    talk8Texture.loadFromFile("talk7.png");
    talk9Texture.loadFromFile("talk8.png");
    mctalk2Texture.loadFromFile("mctalk2.png");
    baekTexture.loadFromFile("baek.png");
    basTexture.loadFromFile("bas.png");
    nextButtonTexture.loadFromFile("nextbutton.png");
    image1Texture.loadFromFile("image1.png");
    image2Texture.loadFromFile("image2.png");

    sf::Sprite talk(talk1Texture), nextButton(nextButtonTexture), image1(image1Texture);
    sf::Sprite baek(baekTexture), bas(basTexture);
    talk.setScale(0.7f, 0.7f);
    talk.setPosition(30.0f, 120.0f);
    nextButton.setPosition(280.0f, 80.0f);
    image1.setScale(0.8f, 0.8f);
    image1.setPosition((window.getSize().x - image1.getGlobalBounds().width) / 2.0f,
        (window.getSize().y - image1.getGlobalBounds().height) / 2.0f);

    // ���� �ý��� ����
    int score = 0;
    const int WIN_SCORE = 3;

    sf::Text scoreText;
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(20, 20);

    // baek�� bas ����
    float baekScale = 0.4f;
    float basScale = 0.4f;
    float baekMoveSpeed = 300.0f;
    float basXSpeed = 200.0f;
    bool basActive = true;
    sf::Vector2f basStartPosition(0, window.getSize().y / 2);

    baek.setScale(baekScale, baekScale);
    bas.setScale(basScale, basScale);

    baek.setPosition(window.getSize().x * 0.75f - baek.getGlobalBounds().width / 2.0f,
        (window.getSize().y - baek.getGlobalBounds().height) / 2.0f);
    bas.setPosition(basStartPosition);

    // ������ ���� ����
    bool movingDown = true;
    sf::Clock clock;

    // ���� ���� ����
    int currentTalk = 0;
    bool gameStarted = false;
    bool image1Displayed = false;
    bool timerStarted = false;
    bool gameSuccess = false;
    bool postGameDialogue = false;
    bool showEndingImages = false;
    bool isPlayingBibimGame = false;
    sf::Clock image1Clock, gameTimer;

    // ������� ��� ����
    sf::Texture gameBackgroundTexture, bibimTexture, lefthandTexture, righthandTexture;
    gameBackgroundTexture.loadFromFile("background.png");
    bibimTexture.loadFromFile("bibim.png");
    lefthandTexture.loadFromFile("lefthand.png");
    righthandTexture.loadFromFile("righthand.png");

    sf::Sprite gameBackground(gameBackgroundTexture), bibim(bibimTexture);
    gameBackground.setScale(
        static_cast<float>(window.getSize().x) / gameBackgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / gameBackgroundTexture.getSize().y
    );
    bibim.setScale(0.75f, 0.75f);
    bibim.setPosition(280.0f, 100.0f);

    sf::Sprite lefthand(lefthandTexture), righthand(righthandTexture);
    sf::Vector2f leftHandStartPos(-100.0f, -150.0f);
    sf::Vector2f rightHandStartPos(400.0f, -150.0f);
    lefthand.setPosition(leftHandStartPos);
    righthand.setPosition(rightHandStartPos);

    float handMovementDistance = 20.0f;
    bool leftHandMoveRight = true, rightHandMoveLeft = true;
    float gauge = 100.0f, gaugeDecreaseRate = 0.5f, gaugeIncreaseRate = 2.5f;

    sf::RectangleShape gaugeBar(sf::Vector2f(gauge * 4, 20));
    gaugeBar.setFillColor(sf::Color::Green);
    gaugeBar.setPosition(100.0f, 50.0f);

    bool spaceKeyPressed = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (!gameStarted && event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left &&
                button.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                gameStarted = true;
                talk.setTexture(talk1Texture);
            }

            if (gameStarted && !image1Displayed && event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left &&
                nextButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                currentTalk++;
                switch (currentTalk) {
                case 1: talk.setTexture(talk1Texture); break;
                case 2: talk.setTexture(talk2Texture); break;
                case 3: talk.setTexture(talk3Texture); break;
                case 4:
                    image1Clock.restart();
                    image1Displayed = true;
                    break;
                }
            }

            if (postGameDialogue && event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left &&
                nextButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                currentTalk++;
                switch (currentTalk) {
                case 4: talk.setTexture(talk4Texture); break;
                case 5: talk.setTexture(talk5Texture); break;
                case 6: talk.setTexture(talk6Texture); break;
                case 7: talk.setTexture(talk7Texture); break;
                case 8: talk.setTexture(talk8Texture); break;
                case 9: talk.setTexture(talk9Texture); break;
                case 10:
                    talk.setTexture(mctalk2Texture);
                    showEndingImages = true;
                    break;
                default:
                    postGameDialogue = false;
                    gameSuccess = false;
                    break;
                }
            }
        }

        // ������� ���� ����
        if (image1Displayed && !timerStarted && image1Clock.getElapsedTime().asSeconds() >= 2) {
            timerStarted = true;
            isPlayingBibimGame = true;
            gameTimer.restart();
        }

        // ������� ����
        if (isPlayingBibimGame && !gameSuccess) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (!spaceKeyPressed) {
                    gauge = std::min(gauge + gaugeIncreaseRate, 100.0f);

                    // �� ������ ó��
                    if (leftHandMoveRight) {
                        lefthand.move(handMovementDistance, 0);
                        leftHandMoveRight = false;
                    }
                    else {
                        lefthand.move(-handMovementDistance, 0);
                        leftHandMoveRight = true;
                    }

                    if (rightHandMoveLeft) {
                        righthand.move(-handMovementDistance, 0);
                        rightHandMoveLeft = false;
                    }
                    else {
                        righthand.move(handMovementDistance, 0);
                        rightHandMoveLeft = true;
                    }

                    spaceKeyPressed = true;
                }
            }
            else {
                spaceKeyPressed = false;
            }

            float elapsedTime = clock.restart().asSeconds();
            gauge -= gaugeDecreaseRate * elapsedTime * 25;

            if (gauge <= 0) {
                std::cout << "Game Over!" << std::endl;
                gauge = 0;
                timerStarted = false;
                isPlayingBibimGame = false;
            }

            // �������� 
            gaugeBar.setSize(sf::Vector2f(gauge * 4, 20));
            gaugeBar.setFillColor(gauge > 50 ? sf::Color::Green : (gauge > 20 ? sf::Color::Yellow : sf::Color::Red));
        }

        // ������� ���� ����
        if (isPlayingBibimGame && !gameSuccess && gameTimer.getElapsedTime().asSeconds() >= 10) {
            std::cout << "Game Success!" << std::endl;
            gameSuccess = true;
            timerStarted = false;
            isPlayingBibimGame = false;
            postGameDialogue = true;
            currentTalk = 3;
            talk.setTexture(talk4Texture);
        }

        // ���� ������ (baek�� bas ������)
        if (showEndingImages) {
            float elapsedTime = clock.restart().asSeconds();

            // ����Ű�� bas �����̱�
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                bas.move(0, -baekMoveSpeed * elapsedTime);

                // ȭ�� ��� ��� ����
                if (bas.getPosition().y < 0) {
                    bas.setPosition(bas.getPosition().x, 0);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                bas.move(0, baekMoveSpeed * elapsedTime);

                // ȭ�� �ϴ� ��� ����
                if (bas.getPosition().y + bas.getGlobalBounds().height > window.getSize().y) {
                    bas.setPosition(bas.getPosition().x, window.getSize().y - bas.getGlobalBounds().height);
                }
            }

            // baek�� �ڵ� ������ (���� �ڵ�� ����)
            float moveAmount = baekMoveSpeed * elapsedTime;
            float currentY = baek.getPosition().y;
            float topBound = 0;
            float bottomBound = window.getSize().y - baek.getGlobalBounds().height;

            if (movingDown) {
                currentY += moveAmount;
                if (currentY >= bottomBound) {
                    currentY = bottomBound;
                    movingDown = false;
                }
            }
            else {
                currentY -= moveAmount;
                if (currentY <= topBound) {
                    currentY = topBound;
                    movingDown = true;
                }
            }
            baek.setPosition(baek.getPosition().x, currentY);

            // bas ������ �� �浹 ó��
            if (basActive) {
                float basMove = basXSpeed * elapsedTime;
                bas.move(basMove, 0);

                // �浹 ���� �ڽ��� �����Ͽ� baek�� �����ʰ� Y�� �κп��� �浹 ó��
                sf::FloatRect adjustedBaekBounds = baek.getGlobalBounds();
                adjustedBaekBounds.left += adjustedBaekBounds.width * 0.7f; // baek �̹����� ������ 70% �κп��� �浹
                adjustedBaekBounds.width *= 0.3f; // �浹 ������ baek �̹��� �ʺ��� 30%�� ����

                // Y�� �浹 �ڽ� ���� (�̹��� �߰� �κ�)
                adjustedBaekBounds.top += adjustedBaekBounds.height * 0.25f; // ������ 25% ��������
                adjustedBaekBounds.height *= 0.3f; // �̹��� ������ 30% �κи� �浹 �������� ����

                if (bas.getGlobalBounds().intersects(adjustedBaekBounds)) {
                    score++;
                    basActive = false;
                    std::cout << "����: " << score << std::endl;

                    if (score < WIN_SCORE) {
                        // ���ο� ��ġ�� ���ġ
                        float randomY = static_cast<float>(rand() % static_cast<int>(window.getSize().y - bas.getGlobalBounds().height));
                        bas.setPosition(basStartPosition.x, randomY);
                        basActive = true;
                    }
                }

                // ȭ�� ��� ó�� - ������ ȭ�� ������ ������ ���� ����
                if (bas.getPosition().x > window.getSize().x) {
                    float randomY = static_cast<float>(rand() % static_cast<int>(window.getSize().y - bas.getGlobalBounds().height));
                    bas.setPosition(basStartPosition.x, randomY);
                }
            }

            // �¸� ���� üũ
            if (score >= WIN_SCORE) {
                std::cout << "���� �¸�!" << std::endl;
                window.close();
            }

            // ���� �ؽ�Ʈ ������Ʈ
            scoreText.setString("����: " + std::to_string(score) + " / " + std::to_string(WIN_SCORE));
        }

        // ������
        window.clear();

        if (gameStarted) {
            window.draw(gameBackground);
            if (currentTalk < 4) {
                window.draw(talk);
                window.draw(nextButton);
            }
            else if (image1Displayed && !timerStarted) {
                window.draw(image1);
            }
            else if (postGameDialogue) {
                if (showEndingImages) {
                    window.draw(baek);
                    if (basActive) {
                        window.draw(bas);
                    }
                    window.draw(scoreText);
                }
                else {
                    window.draw(talk);
                    window.draw(nextButton);
                }
            }
            else if (isPlayingBibimGame) {
                window.draw(bibim);
                window.draw(lefthand);
                window.draw(righthand);
                window.draw(gaugeBar);
            }
        }
        else {
            window.draw(background);
            window.draw(button);
        }

        window.display();
    }

    return 0;
}