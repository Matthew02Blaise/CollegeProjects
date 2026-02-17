#include "ScoreBoard.h"

void ScoreBoard::submitScore(const std::string& playerName, int score) {
    httplib::Client cli("http://dreamlo.com");  // Using HTTP (not HTTPS)
    cli.set_connection_timeout(5, 0);
    cli.set_read_timeout(10, 0);

    std::string url = "/lb/" + DREAMLO_PRIVATE_KEY + "/add/" + playerName + "/" + std::to_string(score);
    auto res = cli.Get(url.c_str());

    if (res && res->status == 200) {
        std::cout << "Score Submitted Successfully!" << std::endl;
    }
    else {
        std::cerr << "Error submitting score! HTTP Status: "
            << (res ? std::to_string(res->status) : "No Response")
            << std::endl;
    }
}

std::string ScoreBoard::getLeaderboardText() {
	httplib::Client cli("http://dreamlo.com");  // Using HTTP
	cli.set_connection_timeout(5, 0);
	cli.set_read_timeout(10, 0);

	// The "pipe-asc" format returns the entries in ascending order.
	std::string url = "/lb/" + DREAMLO_PUBLIC_KEY + "/pipe-dsc/10";
	auto res = cli.Get(url.c_str());

	if (res && res->status == 200) {
		std::string body = res->body;
		std::istringstream iss(body);
		std::string line;
		std::string result;

		// Process each line; each line is expected to be in the format:
		// Name|Score|OtherField1|OtherField2|...
		while (std::getline(iss, line)) {
			if (line.empty())
				continue;
			std::istringstream lineStream(line);
			std::string name, score;

			// Get the name and score (the first two fields)
			if (std::getline(lineStream, name, '|') && std::getline(lineStream, score, '|')) {
				// Format the output as desired (for example "Name : Score")
				result += name + " : " + score + "\n";
			}
		}
		return result;
	}
	else {
		return "Error fetching leaderboard!";
	}
}


std::string ScoreBoard::captureInitials(RenderWindow& window, const Font& font)
{
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	std::string initials;
	Text prompt;
	prompt.setFont(font);
	prompt.setCharacterSize(80);
	prompt.setFillColor(Color::White);
	prompt.setPosition(600, 500); // Adjust the position as needed

	// Create the instructions text
	Text leaderboardInstructions;
	leaderboardInstructions.setFont(font); // Use your loaded font
	leaderboardInstructions.setCharacterSize(40);
	leaderboardInstructions.setFillColor(Color::Yellow);
	leaderboardInstructions.setString("Press Enter when finished menu");

	// Get the local bounds of the text to center it
	FloatRect textRect = leaderboardInstructions.getLocalBounds();
	leaderboardInstructions.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	// Position the text: centered horizontally and 90% down from the top of the screen.
	leaderboardInstructions.setPosition(resolution.x / 2.f, resolution.y * 0.9f);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			// Allow closing the window
			if (event.type == Event::Closed)
			{
				window.close();
				return "";
			}
			// Use TextEntered for capturing text
			if (event.type == Event::TextEntered)
			{
				// Process only standard ASCII characters
				if (event.text.unicode < 128)
				{
					char enteredChar = static_cast<char>(event.text.unicode);
					// Accept only letters (A-Z or a-z) and limit to 3 characters
					if (((enteredChar >= 'A' && enteredChar <= 'Z') ||
						(enteredChar >= 'a' && enteredChar <= 'z')) && initials.size() < 3)
					{
						if (enteredChar >= 'a' && enteredChar <= 'z')
							enteredChar = static_cast<char>(enteredChar - ('a' - 'A'));
						initials.push_back(enteredChar);
						std::cout << "Current initials: " << initials << std::endl;
					}
					// Backspace (ASCII code 8)
					else if (enteredChar == 8 && !initials.empty())
					{
						initials.pop_back();
						std::cout << "After backspace: " << initials << std::endl;
					}
				}
			}
			// Use KeyPressed to detect when the player hits Enter
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Return)
			{
				if (initials.size() == 3)
				{
					return initials;
				}
				else
				{
					std::cout << "Please enter exactly 3 initials." << std::endl;
				}
			}
		}

		// Update prompt text
		prompt.setString("Enter 3 Initials: " + initials);

		window.clear();
		window.draw(prompt);
		window.draw(leaderboardInstructions);
		window.display();
	}
	return initials; // In case the loop ever exits
}
