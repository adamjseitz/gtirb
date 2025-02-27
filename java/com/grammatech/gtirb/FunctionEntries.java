/*
 *  Copyright (C) 2020-2021 GrammaTech, Inc.
 *
 *  This code is licensed under the MIT license. See the LICENSE file in the
 *  project root for license terms.
 *
 *  This project is sponsored by the Office of Naval Research, One Liberty
 *  Center, 875 N. Randolph Street, Arlington, VA 22203 under contract #
 *  N68335-17-C-0700.  The content of the information does not necessarily
 *  reflect the position or policy of the Government and no official
 *  endorsement should be inferred.
 *
 */

package com.grammatech.gtirb;

import java.util.Map;
import java.util.Set;
import java.util.UUID;

/**
 * Schema class for functionEntries auxiliary data.
 * Key: Function UUID.
 * Value: The set of UUIDs of all the entry CodeBlocks for the function.
 * Attached To: Module
 */
public class FunctionEntries {
    private Map<UUID, Set<UUID>> map;

    /**
     * Class Constructor.
     * @param  map  The map of function UUIDs to CodeBlock UUIDs
     * of the function entries.
     */
    public FunctionEntries(Map<UUID, Set<UUID>> map) { this.map = map; }

    /**
     * Get function entries for a function.
     *
     * @param uuid The UUID of a function.
     * @return  A set of {@link CodeBlock} UUIDs.
     */
    public Set<UUID> getFunctionEntries(UUID uuid) {
        return this.map.get(uuid);
    }

    /**
     * Set function entries for a function.
     *
     * @param uuid The UUID of a function.
     * @param entries A set of {@link CodeBlock} UUIDs.
     */
    public void setFunctionEntries(UUID uuid, Set<UUID> entries) {
        this.map.put(uuid, entries);
    }

    /**
     * Get the function entries map.
     *
     * @return  A map of function UUIDs to sets of {@link CodeBlock} UUIDs.
     */
    public Map<UUID, Set<UUID>> getMap() { return this.map; }

    /**
     * Set the function entries map.
     *
     * @param map  A map of function UUIDs to sets of {@link CodeBlock} UUIDs.
     */
    public void setMap(Map<UUID, Set<UUID>> map) { this.map = map; }
}
