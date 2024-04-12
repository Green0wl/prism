constexpr Theme monokai_theme = {
	"monokai",
	Color::hsl(70, 8, 15), // background
	Color::hsl(70, 8, 15), // background_active
	Color::hsl(55, 8, 31).with_alpha(0.7f), // selection
	Color::hsl(60, 36, 96).with_alpha(0.9f), // cursor
	Color::hsl(70, 8, 15), // gutter_background
	Color::hsl(55, 11, 22), // gutter_background_active
	{
		Style(Color::hsl(60, 30, 96)), // text
		Style(Color::hsl(70, 8, 15) + Color::hsl(60, 30, 96).with_alpha(0.5f)), // number
		Style(Color::hsl(70, 8, 15) + Color::hsl(60, 30, 96).with_alpha(0.85f)), // number_active
		Style(Color::hsl(50, 11, 41)), // comments
		Style(Color::hsl(338, 95, 56)), // keywords
		Style(Color::hsl(338, 95, 56)), // operators
		Style(Color::hsl(190, 81, 67), Style::ITALIC), // types
		Style(Color::hsl(261, 100, 75)), // literals
		Style(Color::hsl(54, 70, 68)), // strings
		Style(Color::hsl(261, 100, 75)), // escape sequences
		Style(Color::hsl(80, 76, 53)) // function names
	}
};
