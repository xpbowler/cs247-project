#include "cliDisplay.h"
#include "../asciiart/ascii_graphics.h"
#include "../spells/spell.h"
#include "../enchantments/enchantment.h"
#include "../rituals/ritual.h"
#include "../minions/activatedMinion.h"
#include "../minions/triggeredMinion.h"

using namespace std;

CliDisplay::CliDisplay(Player* player1, Player* player2): player1{player1}, player2{player2} {
    // TODO 
}


void CliDisplay::inspectMinion(bool isPlayer1Turn, int minion) {
    // TODO
}

// Displays all the cards in a player's hand in one row
void CliDisplay::showHand(bool isPlayer1Turn) {
    Player* player = isPlayer1Turn ? player1 : player2;
    for (const auto& card : player->getHand()) {
        showCard(card);
    }
}

void CliDisplay::showBoard() {
    // Display the board in ASCII art, including both players' ritual, graveyard, minions, and player cards

    // Get references to both players
    Player* p1 = player1;
    Player* p2 = player2;

    // Prepare the left and right side: Ritual and Graveyard for each player
    unique_ptr<Card> p1Ritual = p1->getRitual();
    unique_ptr<Card> p2Ritual = p2->getRitual();
    unique_ptr<Card> p1Grave = p1->getGraveyardTop();
    unique_ptr<Card> p2Grave = p2->getGraveyardTop();

    // Rituals
    card_template_t p1RitualTemplate = p1Ritual ? 
        display_ritual(p1Ritual->get_name(), p1Ritual->get_cost(), 
                       static_cast<Ritual*>(p1Ritual.get())->getActivationCost(), 
                       static_cast<Ritual*>(p1Ritual.get())->get_description(), 
                       static_cast<Ritual*>(p1Ritual.get())->getCharges())
        : CARD_TEMPLATE_EMPTY;
    card_template_t p2RitualTemplate = p2Ritual ? 
        display_ritual(p2Ritual->get_name(), p2Ritual->get_cost(), 
                       static_cast<Ritual*>(p2Ritual.get())->getActivationCost(), 
                       static_cast<Ritual*>(p2Ritual.get())->get_description(), 
                       static_cast<Ritual*>(p2Ritual.get())->getCharges())
        : CARD_TEMPLATE_EMPTY;

    // Graveyards
    card_template_t p1GraveTemplate = p1Grave ? showCardAndReturnTemplate(p1Grave) : CARD_TEMPLATE_EMPTY;
    card_template_t p2GraveTemplate = p2Grave ? showCardAndReturnTemplate(p2Grave) : CARD_TEMPLATE_EMPTY;

    // Player cards
    card_template_t p1Card = display_player_card(1, p1->get_name(), p1->getLife(), p1->getMana());
    card_template_t p2Card = display_player_card(2, p2->get_name(), p2->getLife(), p2->getMana());

    // Minions
    vector<unique_ptr<Minion>>& p1Minions = p1->getMinions();
    vector<unique_ptr<Minion>>& p2Minions = p2->getMinions();

    // Prepare minion templates (max 5 per row)
    vector<card_template_t> p1MinionTemplates, p2MinionTemplates;
    for (size_t i = 0; i < 5; ++i) {
        if (i < p1Minions.size()) {
            p1MinionTemplates.push_back(showMinionAndReturnTemplate(p1Minions[i]));
        } else {
            p1MinionTemplates.push_back(CARD_TEMPLATE_EMPTY);
        }
        if (i < p2Minions.size()) {
            p2MinionTemplates.push_back(showMinionAndReturnTemplate(p2Minions[i]));
        } else {
            p2MinionTemplates.push_back(CARD_TEMPLATE_EMPTY);
        }
    }

    // Helper lambda to print a row of card templates
    auto printRow = [](const vector<card_template_t>& row) {
        for (size_t line = 0; line < CARD_TEMPLATE_BORDER.size(); ++line) {
            for (size_t i = 0; i < row.size(); ++i) {
                cout << row[i][line];
            }
            cout << endl;
        }
    };

    // Top row: p2 Ritual, p2 Player, Centre Graphic, p1 Player, p1 Ritual
    vector<card_template_t> topRow = {
        p2RitualTemplate,
        p2Card,
        CENTRE_GRAPHIC,
        p1Card,
        p1RitualTemplate
    };

    // Print top row
    for (size_t line = 0; line < CARD_TEMPLATE_BORDER.size(); ++line) {
        cout << p2RitualTemplate[line]
             << p2Card[line]
             << CENTRE_GRAPHIC[line]
             << p1Card[line]
             << p1RitualTemplate[line]
             << endl;
    }

    // Second row: p2 minions
    printRow(p2MinionTemplates);

    // Middle border
    for (const auto& s : CARD_TEMPLATE_BORDER) cout << s;
    cout << endl;

    // Third row: p1 minions
    printRow(p1MinionTemplates);

    // Bottom row: p2 Grave, empty, empty, empty, p1 Grave
    vector<card_template_t> bottomRow = {
        p2GraveTemplate,
        CARD_TEMPLATE_EMPTY,
        CARD_TEMPLATE_EMPTY,
        CARD_TEMPLATE_EMPTY,
        p1GraveTemplate
    };
    printRow(bottomRow);

    // Helper functions (should be in the class or file scope, but for this context, define here)
    // Returns the card_template_t for a minion
    // (This is a helper, not part of the display interface)
    // If the minion has an activated or triggered ability, use the appropriate display
    // Otherwise, use display_minion_no_ability
    // This function is not visible outside this function, but in real code, should be refactored
    // to a private method of CliDisplay.
    // Also, showCardAndReturnTemplate for graveyard top card.

    // Helper for minion
    auto showMinionAndReturnTemplate = [](const unique_ptr<Minion>& minion) -> card_template_t {
        string name = minion->get_name();
        int cost = minion->get_cost();
        int attack = minion->getAttack();
        int defence = minion->getDefence();
        if (auto act = dynamic_cast<ActivatedMinion*>(minion.get())) {
            return display_minion_activated_ability(name, cost, attack, defence, act->activationCost, ""); // TODO: get ability desc
        } else if (auto trig = dynamic_cast<TriggeredMinion*>(minion.get())) {
            return display_minion_triggered_ability(name, cost, attack, defence, trig->getTrigger().get_description());
        } else {
            return display_minion_no_ability(name, cost, attack, defence);
        }
    };

    // Helper for graveyard/spell/enchantment/ritual
    auto showCardAndReturnTemplate = [](const unique_ptr<Card>& card) -> card_template_t {
        string name = card->get_name();
        int cost = card->get_cost();
        if (auto spell = dynamic_cast<Spell*>(card.get())) {
            return display_spell(name, cost, spell->get_description());
        } else if (auto enchantment = dynamic_cast<Enchantment*>(card.get())) {
            return display_enchantment(name, cost, enchantment->get_description());
        } else if (auto ritual = dynamic_cast<Ritual*>(card.get())) {
            return display_ritual(name, cost, ritual->getActivationCost(), ritual->get_description(), ritual->getCharges());
        } else if (auto minion = dynamic_cast<Minion*>(card.get())) {
            return showMinionAndReturnTemplate(unique_ptr<Minion>(minion));
        } else {
            return CARD_TEMPLATE_EMPTY;
        }
    };
}

void CliDisplay::showCard(const unique_ptr<Card>& card) {
    string name = card->get_name();
    int cost = card->get_cost();
    if (auto spell = dynamic_cast<Spell*>(card.get())) {
        display_spell(name, cost, spell->get_description());
    } else if (auto enchantment = dynamic_cast<Enchantment*>(card.get())) {
        display_enchantment(name, cost, enchantment->get_description());
        // TODO: what is enchantment_attack_defense??
    } else if (auto ritual = dynamic_cast<Ritual*>(card.get())) {
        display_ritual(name, cost, ritual->getActivationCost(), ritual->get_description(), ritual->getCharges());
    } else if (auto minion = dynamic_cast<ActivatedMinion*>(card.get())) {
        display_minion_no_ability(name, cost, minion->getAttack(), minion->getDefence());
    } else if (auto minion = dynamic_cast<TriggeredMinion*>(card.get())) {
        display_minion_triggered_ability(name, cost, minion->getAttack(), minion->getDefence(), minion->getTrigger().get_description());
    } else throw runtime_error("unable to show card");     
}

