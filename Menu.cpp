#include "Menu.h"

Menu::Menu()
{
	this->MenuInit();
}

Menu::~Menu()
{
}

void Menu::MenuInit()
{
	sf::Font f;
	if (!f.loadFromFile("textures/font.otf"))
	{
	}
	this->title.setFont(f);
	title.setString("ENDLESS FLIGHT");
	title.setOrigin(this->title.getLocalBounds().width / 2, this->title.getLocalBounds().height / 2);
	title.setPosition(1024, 768);

	m_playButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_playButton.setString("Play");
	m_playButton.setOrigin(m_playButton.getLocalBounds().width / 2,
		m_playButton.getLocalBounds().height / 2);
	m_playButton.setPosition(m_context->m_window->getSize().x / 2,
		m_context->m_window->getSize().y / 2 - 25.f);
	m_playButton.setCharacterSize(20);

	m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_exitButton.setString("Exit");
	m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2,
		m_exitButton.getLocalBounds().height / 2);
	m_exitButton.setPosition(m_context->m_window->getSize().x / 2,
		m_context->m_window->getSize().y / 2 + 25.f);
	m_exitButton.setCharacterSize(20);

}

void Menu::MenuInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_context->m_window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
            {
                if (!m_isPlayButtonSelected)
                {
                    m_isPlayButtonSelected = true;
                    m_isExitButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::Down:
            {
                if (!m_isExitButtonSelected)
                {
                    m_isPlayButtonSelected = false;
                    m_isExitButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                m_isPlayButtonPressed = false;
                m_isExitButtonPressed = false;

                if (m_isPlayButtonSelected)
                {
                    m_isPlayButtonPressed = true;
                }
                else
                {
                    m_isExitButtonPressed = true;
                }

                break;
            }
            default:
            {
                break;
            }
            }
        }
    }
}
