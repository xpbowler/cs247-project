#include "cliDisplay.h"
#include "ascii_graphics.h"
#include "spell.h"
#include "enchantment.h"
#include "ritual.h"
#include "activatedMinion.h"
#include "triggeredMinion.h"
#include "baseMinion.h"

using namespace std;

const int MAX_ROW_SIZE = 5;

// print a row of card_template_t to an ostream
ostream& printRow(ostream& out, const vector<card_template_t>& row) {
    if (row.size() > MAX_ROW_SIZE) throw runtime_error("too many elements in the row");
    for (const auto& card : row) {
        if (card.size() != row.at(0).size()) throw runtime_error("cards must all be same height to be printed in same row");
    }

    size_t card_height = row.at(0).size();
    for (int i=0;i<card_height;++i) {
        for (size_t j=0;j<row.size();++j) out << row.at(i).at(j);
    }

    return out;
}

card_template_t showMinion(Minion* minion) {
    if (!minion) return CARD_TEMPLATE_BORDER;
    string name = minion->get_name();
    int cost = minion->get_cost();
    int attack = minion->getAttack();
    int defence = minion->getDefence();
    if (auto activatedMinion = dynamic_cast<ActivatedMinion*>(minion)) {
        return display_minion_activated_ability(name, cost, attack, defence, activatedMinion->getActivationCost(), activatedMinion->getDescription());
    } else if (auto triggeredMinion = dynamic_cast<TriggeredMinion*>(minion)) {
        return display_minion_triggered_ability(name, cost, attack, defence, triggeredMinion->getTrigger().get_description());
    } else if (auto baseMinion = dynamic_cast<BaseMinion*>(minion)) {
        return display_minion_no_ability(name, cost, attack, defence);
    } else throw runtime_error("unable to show card");
}

card_template_t showCard(Card* card) {
    if (!card) return CARD_TEMPLATE_BORDER;
    string name = card->get_name();
    int cost = card->get_cost();
    if (auto spell = dynamic_cast<Spell*>(card)) {
        return display_spell(name, cost, spell->get_description());
    } else if (auto enchantment = dynamic_cast<Enchantment*>(card)) {
        return display_enchantment(name, cost, enchantment->getDescription());
        // TODO: what is enchantment_attack_defense??
    } else if (auto ritual = dynamic_cast<Ritual*>(card)) {
        return display_ritual(name, cost, ritual->getActivationCost(), ritual->get_description(), ritual->getCharges());
    } else if (auto minion = dynamic_cast<Minion*>(card)) {
        return showMinion(minion);
    } else throw runtime_error("unable to show card");     
}

void inspectMinionInner(Minion* m) {
    if (!m) return;
    card_template_t mTemplate = showMinion(m);

    const vector<Enchantment*> enchantments = m->getEnchantments();
    vector<card_template_t> enchantmentTemplates;
    for (const auto& enchantment : enchantments) {
        if (enchantmentTemplates.size()<MAX_ROW_SIZE) {
            card_template_t t = display_enchantment(enchantment->get_name(), enchantment->get_cost(), enchantment->getDescription());
            enchantmentTemplates.push_back(t);
        }
    }

    // print minion
    printRow(cout, vector<card_template_t>{mTemplate});
    
    // print past its past 5 enchantments, oldest to newest
    printRow(cout, enchantmentTemplates);
}

CliDisplay::CliDisplay(Player& p1, Player& p2): p1{p1}, p2{p2} {}

void CliDisplay::inspectMinion(bool isPlayer1Turn, int minion) {
    const Player& p = isPlayer1Turn ? p1 : p2;
    int cur = 0;
    for (auto& card : p.getHand()) {
        if (auto m = dynamic_cast<Minion*>(card.get())) {
            if (cur==minion-1) {
                inspectMinionInner(m);
                return;
            } else ++cur;
        }
    }
    throw runtime_error("minion " + to_string(minion) + " not found for isPlayer1Turn: " + to_string(isPlayer1Turn));
}

// Displays all the cards in a player's hand in one row
void CliDisplay::showHand(bool isPlayer1Turn) {
    const Player& p = isPlayer1Turn ? p1 : p2;
    for (const auto& card : p.getHand()) {
        showCard(card.get());
    }
}

// Display the board in ASCII art, including both players' ritual, graveyard, minions, and player cards
void CliDisplay::showBoard() {

    // Prepare the left and right side: Ritual and Graveyard for each player
    Ritual* p1Ritual = p1.getRitual();
    Ritual* p2Ritual = p2.getRitual();
    Card* p1Grave = p1.getGraveyardTop();
    Card* p2Grave = p2.getGraveyardTop();

    // Rituals
    card_template_t p1RitualTemplate = p1Ritual ? 
        display_ritual(p1Ritual->get_name(), p1Ritual->get_cost(), 
                       p1Ritual->getActivationCost(), 
                       p1Ritual->get_description(), 
                       p1Ritual->getCharges())
        : CARD_TEMPLATE_BORDER;
    card_template_t p2RitualTemplate = p2Ritual ? 
        display_ritual(p2Ritual->get_name(), p2Ritual->get_cost(), 
                       p2Ritual->getActivationCost(), 
                       p2Ritual->get_description(), 
                       p2Ritual->getCharges())
        : CARD_TEMPLATE_BORDER;

    // Graveyards
    card_template_t p1GraveTemplate = p1Grave ? showCard(p1Grave) : CARD_TEMPLATE_BORDER;
    card_template_t p2GraveTemplate = p2Grave ? showCard(p2Grave) : CARD_TEMPLATE_BORDER;

    // Player cards
    card_template_t p1Card = display_player_card(1, p1.getName(), p1.getLife(), p1.getMagic());
    card_template_t p2Card = display_player_card(2, p2.getName(), p2.getLife(), p2.getLife());

    // Player minions
    vector<card_template_t> p1Minions, p2Minions;
    for (auto& card : p1.getHand()) {
        if (Minion* minion = dynamic_cast<Minion*>(card.get())) p1Minions.push_back(showMinion(minion));
    }
    for (auto& card : p1.getHand()) {
        if (Minion* minion = dynamic_cast<Minion*>(card.get())) p1Minions.push_back(showMinion(minion));
    }
    while (p1Minions.size() < 5) p1Minions.push_back(CARD_TEMPLATE_EMPTY);
    while (p2Minions.size() < 5) p2Minions.push_back(CARD_TEMPLATE_EMPTY);

    vector<card_template_t> topRow = {p1RitualTemplate, CARD_TEMPLATE_EMPTY, p1Card, CARD_TEMPLATE_EMPTY, p1GraveTemplate};
    vector<card_template_t> bottomRow = {p2RitualTemplate, CARD_TEMPLATE_EMPTY, p2Card, CARD_TEMPLATE_EMPTY, p2GraveTemplate};

    printRow(cout, topRow);
    printRow(cout, p1Minions);
    printRow(cout, vector<card_template_t>{CENTRE_GRAPHIC});
    printRow(cout, p2Minions);
    printRow(cout, bottomRow);
}
