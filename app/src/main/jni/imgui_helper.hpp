#pragma once
#include "imgui/imgui.h"
#include "imgui/tinyformat.h"
#include <stdarg.h>  // For va_start, etc.

static int STYLE = 0;

#define MY_FORMAT(...) std::format(__VA_ARGS__)
#define MY_FORMAT_OS(os, ...) tfm::format(os, __VA_ARGS__)
#define MY_FORMAT_FILE(file, ...) fprint(file, __VA_ARGS__)

#define IM_CLAMP(V, MN, MX)     ((V) < (MN) ? (MN) : (V) > (MX) ? (MX) : (V))

namespace ImGuiHelper {
    bool     getCollapsed();
	float    getWidth();
	float    getHeight();
	float    scaleX(float x);
	float    scaleY(float y);
	void     SetScale(const ImVec2& Scale);
	ImVec4   hexToVec4(int hexValue);
	ImVec4   rgbaToVec4(float r, float g, float b, float a);
	ImVec4   rgbaToVec4(ImColor& col);
	ImVec2   getTextLength(std::string text);
	void     renderCombo(std::string title, std::vector<std::string>items, int& index, int comboWidth);
	void     drawTabHorizontally(std::string childName, ImVec2 childSize, std::vector<std::string>tabNames, int& selectedSubTab, ImVec4 col = rgbaToVec4(140, 140, 140, 255)); // draws togglebuttons(tabs) in a child
	bool     Button(ImFont *fontBtn, const char *label, ImVec2 size);
	bool     BeginLogo(ImFont *fontBtn, ImFont *font, ImVec2 size, ImTextureID min_texture, ImTextureID user_texture_id, const char *title, bool show_close_button, ImGuiWindowFlags flags);
    void     LoadingIndicatorCircle(const char *label, const char *overlay, float fraction, const float indicator_radius, const ImVec4 & main_color, const ImVec4 & backdrop_color, const int circle_count, const float speed);
	void     Progress(bool* out);
	bool     Checkbox2(const char* label, bool* v);
	bool     Checkbox_(const char* label, bool* v);

	bool     SliderInt_3(const char* label, int* v, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
	bool     SliderInt_2(const char* label, int* v, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
	bool	 SliderInt_(const char* label, int* v, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);

	bool     SliderFloat_3(const char* label, float* v, float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
	bool     SliderFloat_2(const char* label, float* v, float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
	bool     SliderFloat_(const char* label, float* v, float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);

	void     chromaText(std::string text, float sat, float value, float alpha, float speed, float offset, float range);
    void     CircleImageFilled(ImTextureID TextureId, const ImVec2& CentrePos, float fRadius, ImColor Color, int iNumSegments);
    void     ToggleButton(ImFont* font, const char* label, const char* str_id, bool* v);
    bool     Toggle( const char* label, bool* v );
    void     GetTouchPos(struct AInputEvent *event, int ids[], float xs[], float ys[]);
    void     SetTouchPos(struct AInputEvent *event, float xs, float ys);
    
    
    bool     ListBox(const char* label, int* currIndex, std::vector<std::string>& values, int height_in_items = -1);
    
    inline std::string Format(const char* fmt, ...){
        int size = 512;
        char* buffer = 0;
        buffer = new char[size];
        va_list vl;
        va_start(vl, fmt);
        int nsize = vsnprintf(buffer, size, fmt, vl);
        if(size<=nsize){ //fail delete buffer and try again
            delete[] buffer;
            buffer = 0;
            buffer = new char[nsize+1]; //+1 for /0
            nsize = vsnprintf(buffer, size, fmt, vl);
        }
        std::string ret(buffer);
        va_end(vl);
        delete[] buffer;
        return ret;
    }
    
    inline std::string FormatS(const std::string fmt, ...) {
        int size = ((int)fmt.size()) * 2 + 50;   // Use a rubric appropriate for your code
        std::string str;
        va_list ap;
        while (1) {     // Maximum two passes on a POSIX system...
            str.resize(size);
            va_start(ap, fmt);
            int n = vsnprintf((char *)str.data(), size, fmt.c_str(), ap);
            va_end(ap);
            if (n > -1 && n < size) {  // Everything worked
                str.resize(n);
                return str;
            }
            if (n > -1)  // Needed size returned
                size = n + 1;   // For null char
            else
                size *= 2;      // Guess at a larger size (OS specific)
        }
        return str;
    }
}

struct ImGuiTextFilter2 : public ImGuiTextFilter {
	IMGUI_API bool      Draw2(const char* label = "Filter (inc,-exc)", float width = 0.0f);  // filter.Draw | Helper calling InputText+Build
};


inline ImVec4 hex(int hex, float alpha = 1.0f)
{
    int red = (hex >> 16) & 255;
    int green = (hex >> 8) & 255;
    int blue = (hex >> 0) & 255;
    return ImVec4(red / 255.f, green / 255.f, blue / 255.f, alpha);
}

// convert to ImVec4 from hex
inline ImVec4 operator "" _h(unsigned long long h) {
    return hex(static_cast<int>(h));
}



struct ImVec3
{
	float x, y, z;
	ImVec4 vec4;
	ImColor u32;
	
	ImVec3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
	{
		x = _x;
		y = _y;
		z = _z;
		
		vec4.x = _x;
		vec4.y = _y;
		vec4.z = _z;
		vec4.w = 1.f;
		
		u32.Value.x = _x;
		u32.Value.y = _y;
		u32.Value.z = _z;
		u32.Value.w = 1.f;
	};
};
