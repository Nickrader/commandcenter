#include "MeleeManager.h"
#include "Util.h"
#include "CCBot.h"

MeleeManager::MeleeManager(CCBot & bot)
    : MicroManager(bot)
{

}

void MeleeManager::executeMicro(const std::vector<CCUnit> & targets)
{
    assignTargets(targets);
}

void MeleeManager::assignTargets(const std::vector<CCUnit> & targets)
{
    const std::vector<CCUnit> & meleeUnits = getUnits();

    // figure out targets
    std::vector<CCUnit> meleeUnitTargets;
    for (auto target : targets)
    {
        if (!target) { continue; }
        if (target->is_flying) { continue; }
        if (target->unit_type == sc2::UNIT_TYPEID::ZERG_EGG) { continue; }
        if (target->unit_type == sc2::UNIT_TYPEID::ZERG_LARVA) { continue; }

        meleeUnitTargets.push_back(target);
    }

    // for each meleeUnit
    for (auto & meleeUnit : meleeUnits)
    {
        BOT_ASSERT(meleeUnit, "melee unit is null");

        // if the order is to attack or defend
        if (order.getType() == SquadOrderTypes::Attack || order.getType() == SquadOrderTypes::Defend)
        {
            // run away if we meet the retreat critereon
            if (meleeUnitShouldRetreat(meleeUnit, targets))
            {
                CCPosition fleeTo(m_bot.GetStartLocation());

                Micro::SmartMove(meleeUnit, fleeTo, m_bot);
            }
            // if there are targets
            else if (!meleeUnitTargets.empty())
            {
                // find the best target for this meleeUnit
                CCUnit target = getTarget(meleeUnit, meleeUnitTargets);

                // attack it
                Micro::SmartAttackUnit(meleeUnit, target, m_bot);
            }
            // if there are no targets
            else
            {
                // if we're not near the order position
                if (Util::Dist(meleeUnit->pos, order.getPosition()) > 4)
                {
                    // move to it
                    Micro::SmartMove(meleeUnit, order.getPosition(), m_bot);
                }
            }
        }

        if (m_bot.Config().DrawUnitTargetInfo)
        {
            // TODO: draw the line to the unit's target
        }
    }
}

// get a target for the meleeUnit to attack
CCUnit MeleeManager::getTarget(CCUnit meleeUnit, const std::vector<CCUnit> & targets)
{
    BOT_ASSERT(meleeUnit, "null melee unit in getTarget");

    int highPriority = 0;
    double closestDist = std::numeric_limits<double>::max();
    CCUnit closestTarget = nullptr;

    // for each target possiblity
    for (auto & targetUnit : targets)
    {
        BOT_ASSERT(targetUnit, "null target unit in getTarget");

        int priority = getAttackPriority(meleeUnit, targetUnit);
        float distance = Util::Dist(meleeUnit->pos, targetUnit->pos);

        // if it's a higher priority, or it's closer, set it
        if (!closestTarget || (priority > highPriority) || (priority == highPriority && distance < closestDist))
        {
            closestDist = distance;
            highPriority = priority;
            closestTarget = targetUnit;
        }
    }

    return closestTarget;
}

// get the attack priority of a type in relation to a zergling
int MeleeManager::getAttackPriority(CCUnit attacker, CCUnit unit)
{
    BOT_ASSERT(unit, "null unit in getAttackPriority");

    if (Util::IsCombatUnit(unit, m_bot))
    {
        return 10;
    }

    if (Util::IsWorker(unit))
    {
        return 9;
    }

    return 1;
}

bool MeleeManager::meleeUnitShouldRetreat(CCUnit meleeUnit, const std::vector<CCUnit> & targets)
{
    // TODO: should melee units ever retreat?
    return false;
}
