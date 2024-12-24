lv_color_t adjust_color(uint32_t color, float darken_factor, float saturation_reduction_factor) {
	// Extract RGB components
	uint8_t red = (color >> 16) & 0xFF;
	uint8_t green = (color >> 8) & 0xFF;
	uint8_t blue = color & 0xFF;

	// Darken components
	red = static_cast<uint8_t>(red * darken_factor);
	green = static_cast<uint8_t>(green * darken_factor);
	blue = static_cast<uint8_t>(blue * darken_factor);

	// Convert to grayscale (simple average)
	uint8_t grayscale = static_cast<uint8_t>((red + green + blue) / 3);

	// Apply the saturation reduction by blending the grayscale value with the original color
	red = static_cast<uint8_t>(red * (1 - saturation_reduction_factor) + grayscale * saturation_reduction_factor);
	green = static_cast<uint8_t>(green * (1 - saturation_reduction_factor) + grayscale * saturation_reduction_factor);
	blue = static_cast<uint8_t>(blue * (1 - saturation_reduction_factor) + grayscale * saturation_reduction_factor);

	// Return the adjusted color using lv_color_make with the desaturated, darkened components
	return lv_color_make(red, green, blue);
}
