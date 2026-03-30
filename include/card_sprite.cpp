// card_sprite.cpp

#include "card_sprite.h"

static const float    CARD_PADDING       = 5.0f;
static const unsigned CORNER_RANK_SIZE   = 14;
static const unsigned CORNER_SUIT_SIZE   = 12;
static const unsigned CENTER_SUIT_SIZE   = 32;
static const unsigned MONOGRAM_SIZE      = 20;

// ── Colours ─────────────────────────────────────────────────────────────────
static const sf::Color CLR_FACE_FILL    (255, 252, 240);   // Warm white
static const sf::Color CLR_FACE_HOVER   (240, 242, 255);   // Soft blue tint on hover
static const sf::Color CLR_FACE_BORDER  (180, 160, 120);   // Tan outline
static const sf::Color CLR_SEL_BORDER   (255, 215,   0);   // Gold outline when selected
static const sf::Color CLR_BACK_FILL    (130,  20,  20);   // Dark maroon
static const sf::Color CLR_BACK_HOVER   (150,  30,  30);
static const sf::Color CLR_BACK_BORDER  ( 80,  10,  10);
static const sf::Color CLR_INNER_BORDER (180, 150,  60);   // Gold inner ring on back
static const sf::Color CLR_MONO         (180, 150,  60);   // "RM" monogram colour
static const sf::Color CLR_RED_SUIT     (200,  20,  20);
static const sf::Color CLR_BLACK_SUIT   ( 20,  20,  20);

// ── Constructor ──────────────────────────────────────────────────────────────
card_sprite::card_sprite()
    : bFaceUp(false), bSelected(false), bHover(false), clrSuit(CLR_BLACK_SUIT)
{
    rctBody.setSize(sf::Vector2f(CARD_WIDTH, CARD_HEIGHT));

    rctInner.setFillColor(sf::Color::Transparent);
    rctInner.setOutlineColor(CLR_INNER_BORDER);
    rctInner.setOutlineThickness(2.0f);
    rctInner.setSize(sf::Vector2f(CARD_WIDTH  - CARD_PADDING * 2,
                                  CARD_HEIGHT - CARD_PADDING * 2));

    update_style();
}

// ── Public setters ────────────────────────────────────────────────────────────
void card_sprite::set_card(const card& crdCard, const sf::Font& fntFont)
{
    sf::String strRank = rank_to_string(crdCard.rank());
    sf::String strSuit = suit_to_string(crdCard.suit());
    clrSuit = suit_to_color(crdCard.suit());

    txtRankTop.setFont(fntFont);
    txtRankTop.setString(strRank);
    txtRankTop.setCharacterSize(CORNER_RANK_SIZE);
    txtRankTop.setFillColor(clrSuit);

    txtSuitTop.setFont(fntFont);
    txtSuitTop.setString(strSuit);
    txtSuitTop.setCharacterSize(CORNER_SUIT_SIZE);
    txtSuitTop.setFillColor(clrSuit);

    txtCenter.setFont(fntFont);
    txtCenter.setString(strSuit);
    txtCenter.setCharacterSize(CENTER_SUIT_SIZE);
    txtCenter.setFillColor(clrSuit);

    txtRankBtm.setFont(fntFont);
    txtRankBtm.setString(strRank);
    txtRankBtm.setCharacterSize(CORNER_RANK_SIZE);
    txtRankBtm.setFillColor(clrSuit);
    txtRankBtm.setRotation(180.0f);

    txtSuitBtm.setFont(fntFont);
    txtSuitBtm.setString(strSuit);
    txtSuitBtm.setCharacterSize(CORNER_SUIT_SIZE);
    txtSuitBtm.setFillColor(clrSuit);
    txtSuitBtm.setRotation(180.0f);

    txtMonogram.setFont(fntFont);
    txtMonogram.setString("RM");
    txtMonogram.setCharacterSize(MONOGRAM_SIZE);
    txtMonogram.setFillColor(CLR_MONO);

    update_layout();
}

void card_sprite::set_position(sf::Vector2f vPos)
{
    rctBody.setPosition(vPos);
    update_layout();
}

void card_sprite::set_face_up(bool bUp)
{
    bFaceUp = bUp;
    update_style();
}

void card_sprite::set_selected(bool bSel)
{
    bSelected = bSel;
    update_style();
}

void card_sprite::set_hover(bool bHov)
{
    bHover = bHov;
    update_style();
}

// ── Public getters ────────────────────────────────────────────────────────────
sf::Vector2f card_sprite::get_position() const
{
    return rctBody.getPosition();
}

bool card_sprite::contains(sf::Vector2f vPoint) const
{
    return rctBody.getGlobalBounds().contains(vPoint);
}

bool card_sprite::isFaceUp() const
{
    return bFaceUp;
}

bool card_sprite::isSelected() const
{
    return bSelected;
}

// ── Draw ──────────────────────────────────────────────────────────────────────
void card_sprite::draw(sf::RenderWindow& wndTarget) const
{
    wndTarget.draw(rctBody);

    if (bFaceUp)
    {
        wndTarget.draw(txtRankTop);
        wndTarget.draw(txtSuitTop);
        wndTarget.draw(txtCenter);
        wndTarget.draw(txtRankBtm);
        wndTarget.draw(txtSuitBtm);
    }
    else
    {
        wndTarget.draw(rctInner);
        wndTarget.draw(txtMonogram);
    }
}

// ── Private helpers ───────────────────────────────────────────────────────────
void card_sprite::update_style()
{
    if (bFaceUp)
    {
        rctBody.setFillColor(bHover ? CLR_FACE_HOVER : CLR_FACE_FILL);
        rctBody.setOutlineColor(bSelected ? CLR_SEL_BORDER : CLR_FACE_BORDER);
        rctBody.setOutlineThickness(bSelected ? 3.0f : 1.5f);
    }
    else
    {
        rctBody.setFillColor(bHover ? CLR_BACK_HOVER : CLR_BACK_FILL);
        rctBody.setOutlineColor(bSelected ? CLR_SEL_BORDER : CLR_BACK_BORDER);
        rctBody.setOutlineThickness(bSelected ? 3.0f : 1.5f);
    }
}

void card_sprite::update_layout()
{
    sf::Vector2f vPos = rctBody.getPosition();

    // Inner border for face-down back
    rctInner.setPosition(sf::Vector2f(vPos.x + CARD_PADDING, vPos.y + CARD_PADDING));

    // Top-left corner: rank above suit
    txtRankTop.setPosition(sf::Vector2f(vPos.x + 4.0f, vPos.y + 2.0f));
    txtSuitTop.setPosition(sf::Vector2f(vPos.x + 4.0f, vPos.y + 17.0f));

    // Centre suit symbol — centred in card body
    sf::FloatRect frtCenter = txtCenter.getLocalBounds();
    txtCenter.setOrigin(
        frtCenter.left + frtCenter.width  / 2.0f,
        frtCenter.top  + frtCenter.height / 2.0f
    );
    txtCenter.setPosition(sf::Vector2f(
        vPos.x + CARD_WIDTH  / 2.0f,
        vPos.y + CARD_HEIGHT / 2.0f
    ));

    // Bottom-right corner: rank/suit rotated 180°, origin centred for correct placement
    sf::FloatRect frtRankBtm = txtRankBtm.getLocalBounds();
    txtRankBtm.setOrigin(
        frtRankBtm.left + frtRankBtm.width  / 2.0f,
        frtRankBtm.top  + frtRankBtm.height / 2.0f
    );
    txtRankBtm.setPosition(sf::Vector2f(
        vPos.x + CARD_WIDTH  - 8.0f,
        vPos.y + CARD_HEIGHT - 5.0f
    ));

    sf::FloatRect frtSuitBtm = txtSuitBtm.getLocalBounds();
    txtSuitBtm.setOrigin(
        frtSuitBtm.left + frtSuitBtm.width  / 2.0f,
        frtSuitBtm.top  + frtSuitBtm.height / 2.0f
    );
    txtSuitBtm.setPosition(sf::Vector2f(
        vPos.x + CARD_WIDTH  - 8.0f,
        vPos.y + CARD_HEIGHT - 20.0f
    ));

    // Monogram centred for face-down back
    sf::FloatRect frtMono = txtMonogram.getLocalBounds();
    txtMonogram.setOrigin(
        frtMono.left + frtMono.width  / 2.0f,
        frtMono.top  + frtMono.height / 2.0f
    );
    txtMonogram.setPosition(sf::Vector2f(
        vPos.x + CARD_WIDTH  / 2.0f,
        vPos.y + CARD_HEIGHT / 2.0f
    ));
}

// ── Static converters ─────────────────────────────────────────────────────────
sf::String card_sprite::rank_to_string(int iRank)
{
    if (iRank == JOKER) return "J";
    if (iRank == ACE)   return "A";
    if (iRank == JACK)  return "J";
    if (iRank == QUEEN) return "Q";
    if (iRank == KING)  return "K";
    return std::to_string(iRank);
}

sf::String card_sprite::suit_to_string(int iSuit)
{
    switch (iSuit)
    {
        case SPADES:   return sf::String(static_cast<sf::Uint32>(0x2660)); // ♠
        case HEARTS:   return sf::String(static_cast<sf::Uint32>(0x2665)); // ♥
        case DIAMONDS: return sf::String(static_cast<sf::Uint32>(0x2666)); // ♦
        case CLUBS:    return sf::String(static_cast<sf::Uint32>(0x2663)); // ♣
        case RED:
        case BLACK:    return "*";
        default:       return "?";
    }
}

sf::Color card_sprite::suit_to_color(int iSuit)
{
    switch (iSuit)
    {
        case HEARTS:
        case DIAMONDS:
        case RED:    return CLR_RED_SUIT;
        default:     return CLR_BLACK_SUIT;
    }
}
