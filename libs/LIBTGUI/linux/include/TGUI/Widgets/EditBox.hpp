/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2023 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef TGUI_EDIT_BOX_HPP
#define TGUI_EDIT_BOX_HPP


#include <TGUI/Widgets/ClickableWidget.hpp>
#include <TGUI/Renderers/EditBoxRenderer.hpp>
#include <TGUI/Rect.hpp>
#include <TGUI/Text.hpp>

#if !TGUI_EXPERIMENTAL_USE_STD_MODULE
    #include <regex>
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TGUI_MODULE_EXPORT namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Edit box widget
    ///
    /// An edit box is a single line input field. It has options like setting a password character or displaying a default text.
    /// If you are looking for something with multiple lines, word-wrap and a scrollbar then check out the TextArea class.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API EditBox : public ClickableWidget
    {
    public:

        using Ptr = std::shared_ptr<EditBox>; //!< Shared widget pointer
        using ConstPtr = std::shared_ptr<const EditBox>; //!< Shared constant widget pointer

        static constexpr const char StaticWidgetType[] = "EditBox"; //!< Type name of the widget


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief The text alignment
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        enum class Alignment
        {
            /// Put the text on the left side (default)
            Left,

            /// Center the text
            Center,

            /// Put the text on the right side (e.g. for numbers)
            Right
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Predefined input validators
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        struct Validator
        {
            static TGUI_API const char32_t* All;   //!< Accept any input
            static TGUI_API const char32_t* Int;   //!< Accept negative and positive integers
            static TGUI_API const char32_t* UInt;  //!< Accept only positive integers
            static TGUI_API const char32_t* Float; //!< Accept decimal numbers
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// @brief Constructor
        /// @param typeName     Type of the widget
        /// @param initRenderer Should the renderer be initialized? Should be true unless a derived class initializes it.
        /// @see create
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        EditBox(const char* typeName = StaticWidgetType, bool initRenderer = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a new edit box widget
        ///
        /// @return The new edit box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD static EditBox::Ptr create();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another edit box
        ///
        /// @param editBox  The other edit box
        ///
        /// @return The new edit box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD static EditBox::Ptr copy(const EditBox::ConstPtr& editBox);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        /// @return Temporary pointer to the renderer that may be shared with other widgets using the same renderer
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD EditBoxRenderer* getSharedRenderer() override;
        TGUI_NODISCARD const EditBoxRenderer* getSharedRenderer() const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        /// @return Temporary pointer to the renderer
        /// @warning After calling this function, the widget has its own copy of the renderer and it will no longer be shared.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD EditBoxRenderer* getRenderer() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the edit box
        ///
        /// @param size  The new size of the edit box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(const Layout2d& size) override;
        using Widget::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Enables or disables the widget
        /// @param enabled  Is the widget enabled?
        ///
        /// The disabled widget will no longer receive events and thus no longer send callbacks.
        /// All widgets are enabled by default.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setEnabled(bool enabled) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the text of the editbox
        ///
        /// @param text  The new text
        ///
        /// The last characters of the text might be removed in the following situations:
        /// - You have set a character limit and this text contains too much characters.
        /// - You have limited the text width and the text does not fit inside the EditBox.
        ///
        /// @see setMaximumCharacters
        /// @see limitTextWidth
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setText(const String& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the text inside the edit box. This text is not affected by the password character
        ///
        /// @return The text of the edit box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD const String& getText() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the default text of the editbox. This is the text drawn when the edit box is empty
        ///
        /// This text is not affected by the password character.
        ///
        /// @param text  The new default text
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setDefaultText(const String& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the default text of the edit box. This is the text drawn when the edit box is empty
        ///
        /// This text is not affected by the password character.
        ///
        /// @return The default text of the edit box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD const String& getDefaultText() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Selects text in the edit box
        ///
        /// @param start  The index of the first character to select
        /// @param length Amount of character to select
        ///
        /// When no parameters are provided, the entire text is selected.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void selectText(std::size_t start = 0, std::size_t length = String::npos);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the text that you currently have selected. This text is not affected by the password character
        ///
        /// @return The selected text of the edit box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD String getSelectedText() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets a password character
        ///
        /// @param passwordChar  The new password character.
        ///                      If set to 0 then there is no password character
        ///
        /// When the text width is limited then this function might remove the last characters in the text if they no
        /// longer fit in the EditBox. You can avoid this by setting LimitTextWidth to false (which is the default).
        ///
        /// @see limitTextWidth
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setPasswordCharacter(char32_t passwordChar);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the password character
        ///
        /// @return  The password character that is currently being used.
        ///          When no password character is used then this function returns 0
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD char32_t getPasswordCharacter() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the character limit
        ///
        /// @param maxChars  The new character limit. Set it to 0 to disable the limit
        ///
        /// This character limit is disabled by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMaximumCharacters(unsigned int maxChars);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the character limit
        ///
        /// @return The character limit.
        ///         The function will return 0 when there is no limit
        ///
        /// There is no character limit by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD unsigned int getMaximumCharacters() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the text alignment
        ///
        /// @param alignment  The new text alignment
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setAlignment(Alignment alignment);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Gets the current text alignment
        ///
        /// @return Text alignment
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD Alignment getAlignment() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Should the text width be limited or should you be able to type even if the edit box is full?
        ///
        /// @param limitWidth  Should there be a text width limit or not
        ///
        /// When set to true, you will no longer be able to add text when the edit box is full.
        /// The default value is false.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void limitTextWidth(bool limitWidth = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Checks if the text width is limited to the size of the edit box
        ///
        /// @return Is the text width limit or not
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD bool isTextWidthLimited() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes the edit box read-only or make it writable again
        ///
        /// @param readOnly  Should the edit box be read-only?
        ///
        /// When the edit box is read-only, you can no longer delete characters and type text.
        /// Selecting text, copying text and even calling the setText function will still work.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setReadOnly(bool readOnly = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Checks if the edit box read-only or writable
        ///
        /// @return Is the edit box read-only?
        ///
        /// When the edit box is read-only, you can no longer delete characters and type text.
        /// Selecting text, copying text and even calling the setText function will still work.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD bool isReadOnly() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the blinking caret to after a specific character
        ///
        /// @param charactersBeforeCaret  The new position
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setCaretPosition(std::size_t charactersBeforeCaret);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns after which character the blinking cursor is currently located
        ///
        /// @return Characters before the caret
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD std::size_t getCaretPosition() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Defines how the text input should look like
        ///
        /// @param regex  Valid regular expression for std::regex to match on text changes
        ///
        /// @return True when validator was changed, false when std::regex_error was thrown internally.
        ///
        /// When the regex does not match when calling the setText function then the edit box contents will be cleared.
        /// When it does not match when the user types a character in the edit box, then the input character is rejected.
        ///
        /// Examples:
        /// @code
        /// edit1->setInputValidator(EditBox::Validator::Int);
        /// edit2->setInputValidator("[a-zA-Z][a-zA-Z0-9]*");
        /// @endcode
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setInputValidator(const String& regex = U".*");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the regex to which the text is matched
        ///
        /// @return Regex to match the text with on every text change
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD const String& getInputValidator() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Places a suffix at the right side of the edit box
        ///
        /// @param suffix  Text to show on right side of edit box
        ///
        /// Setting a suffix can be useful for inputting numbers where you want to unit to be displayed inside the edit box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSuffix(const String& suffix);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the suffix currently displayed on the right side of the edit box
        ///
        /// @return Text shown on right side of edit box
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD const String& getSuffix() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Focus or unfocus the widget
        /// @param focused  Is the widget focused?
        ///
        /// When a widget is focused, the previously focused widget will be unfocused.
        ///
        /// @warning This function only works properly when the widget was already added to its parent (e.g. the Gui).
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setFocused(bool focused) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the mouse position (which is relative to the parent widget) lies on top of the widget
        /// @return Is the mouse on top of the widget?
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD bool isMouseOnWidget(Vector2f pos) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool leftMousePressed(Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseMoved(Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void keyPressed(const Event::KeyEvent& event) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Called by the parent of the widget to check if keyPressed would process the event
        ///
        /// @param event  Key event that took place
        ///
        /// @return True if the event would be handled by the widget, false if the key event doesn't affect the widget
        ///
        /// @since TGUI 1.1
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool canHandleKeyPress(const Event::KeyEvent& event) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void textEntered(char32_t key) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Draw the widget to a render target
        ///
        /// @param target Render target to draw to
        /// @param states Current render states
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw(BackendRenderTarget& target, RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves a signal based on its name
        ///
        /// @param signalName  Name of the signal
        ///
        /// @return Signal that corresponds to the name
        ///
        /// @throw Exception when the name does not match any signal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD Signal& getSignal(String signalName) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Function called when one of the properties of the renderer is changed
        ///
        /// @param property  Name of the property that was changed
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void rendererChanged(const String& property) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Saves the widget as a tree node in order to save it to a file
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD std::unique_ptr<DataIO::Node> save(SavingRenderersMap& renderers) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Loads the widget from a tree of nodes
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void load(const std::unique_ptr<DataIO::Node>& node, const LoadingRenderersMap& renderers) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Called when the text size is changed (either by setTextSize or via the renderer)
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateTextSize() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the total width that the text is going to take
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD float getFullTextWidth() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the size without the borders
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD Vector2f getInnerSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the width of the edit box minus the padding.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD float getVisibleEditBoxWidth() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function will search after which character the caret should be placed. It will not change the caret position.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD std::size_t findCaretPosition(float posX);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Removes the selected characters. This function is called when pressing backspace, delete or a letter while there were
        // some characters selected.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void deleteSelectedCharacters();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Recalculates the position of the texts.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void recalculateTextPositions();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Updates the internal texts after SelStart or SelEnd changed.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateSelection();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update the color of the Text objects
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateTextColor();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called every frame with the time passed since the last frame.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool updateTime(Duration elapsedTime) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD Widget::Ptr clone() const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Updates m_selEnd with a new value and emits the onCaretPositionChange signal
        // @param newValue the value to assign to m_selEnd.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateSelEnd(const std::size_t newValue);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Handles "Backspace" key press
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void backspaceKeyPressed();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Handles "Delete" key press
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void deleteKeyPressed();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Handles "Ctrl+C" key press (or equivalent on macOS)
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void copySelectedTextToClipboard();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Handles "Ctrl+X" key press (or equivalent on macOS)
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void cutSelectedTextToClipboard();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Handles "Ctrl+V" key press (or equivalent on macOS)
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void pasteTextFromClipboard();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Handles "ArrowLeft" key press
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void moveCaretLeft(bool shiftPressed);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Handles "ArrowRight" key press
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void moveCaretRight(bool shiftPressed);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Handles "Ctrl+ArrowLeft" key press (or equivalent on macOS)
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void moveCaretWordBegin();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Handles "Ctrl+ArrowRight" key press (or equivalent on macOS)
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void moveCaretWordEnd();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public:

        SignalString             onTextChange          = {"TextChanged"};          //!< The text was changed. Optional parameter: new text
        SignalString             onReturnKeyPress      = {"ReturnKeyPressed"};     //!< The return key was pressed. Optional parameter: text in the edit box
        SignalString             onReturnOrUnfocus     = {"ReturnOrUnfocused"};    //!< The return key was pressed or the edit box was unfocused. Optional parameter: text in the edit box
        SignalTyped<std::size_t> onCaretPositionChange = {"CaretPositionChanged"}; //!< The caret's position was changed. Optional parameter: new caret position


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        // Is the caret visible or not?
        bool          m_caretVisible = true;

        // When this boolean is true then you can no longer add text when the EditBox is full.
        // Changing it to false will allow you to scroll the text (default).
        // You can change the boolean with the limitTextWidth(bool) function.
        bool          m_limitTextWidth = false;

        bool          m_readOnly = false;

        // The text inside the edit box
        String m_text;
        String m_displayedText; // Same as m_text unless a password char is set

        String m_regexString = U".*";
        std::wregex m_regex;

        // The text alignment
        Alignment     m_textAlignment = Alignment::Left;

        // The selection
        std::size_t   m_selChars = 0;
        std::size_t   m_selStart = 0;
        std::size_t   m_selEnd = 0;

        // The password character
        char32_t      m_passwordChar = '\0';

        // The maximum allowed characters.
        // Zero by default, meaning no limit.
        unsigned int  m_maxChars = 0;

        // When the text width is not limited, you can scroll the edit box and only a part will be visible.
        unsigned int  m_textCropPosition = 0;

        // The rectangle behind the selected text
        FloatRect     m_selectedTextBackground;

        // The blinking caret
        FloatRect     m_caret = {0, 0, 1, 0};

        // Is there a possibility that the user is going to double click?
        bool m_possibleDoubleClick = false;

        // We need three texts for drawing + one for the default text + one more for calculations.
        Text m_textBeforeSelection;
        Text m_textSelection;
        Text m_textAfterSelection;
        Text m_defaultText;
        Text m_textFull;
        Text m_textSuffix;

        Sprite m_sprite;
        Sprite m_spriteHover;
        Sprite m_spriteDisabled;
        Sprite m_spriteFocused;

        // Cached renderer properties
        Borders m_bordersCached;
        Padding m_paddingCached;
        Color   m_borderColorCached;
        Color   m_borderColorHoverCached;
        Color   m_borderColorDisabledCached;
        Color   m_borderColorFocusedCached;
        Color   m_backgroundColorCached;
        Color   m_backgroundColorHoverCached;
        Color   m_backgroundColorDisabledCached;
        Color   m_backgroundColorFocusedCached;
        Color   m_caretColorCached;
        Color   m_caretColorHoverCached;
        Color   m_caretColorFocusedCached;
        Color   m_selectedTextBackgroundColorCached;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_EDIT_BOX_HPP
