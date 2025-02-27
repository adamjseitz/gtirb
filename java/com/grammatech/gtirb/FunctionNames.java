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
import java.util.UUID;

/**
 * Schema class for functionBlocks auxiliary data.
 * Key: Function UUID.
 * Value: The UUID of a Symbol whose name field contains the name of the
 * function. Attached To: Module
 */
public class FunctionNames {
    private Map<UUID, UUID> map;

    /**
     * Class Constructor.
     * @param  map  The map of function UUIDs to a {@link Symbol} UUID
     * with the name of the function.
     */
    public FunctionNames(Map<UUID, UUID> map) { this.map = map; }

    /**
     * Get the name of a function.
     *
     * @param uuid The UUID of a function.
     * @return  A {@link Symbol} UUID.
     */
    public UUID getFunctionName(UUID uuid) { return this.map.get(uuid); }

    /**
     * Set name of a function.
     *
     * @param functionUuid The UUID of a function.
     * @param symbolUuid A {@link Symbol} UUID.
     */
    public void setFunctionName(UUID functionUuid, UUID symbolUuid) {
        this.map.put(functionUuid, symbolUuid);
    }

    /**
     * Get the function names map.
     *
     * @return  A map of function UUIDs to {@link Symbol} UUIDs.
     */
    public Map<UUID, UUID> getMap() { return this.map; }

    /**
     * Set the function names map.
     *
     * @param map   A map of function UUIDs to {@link Symbol} UUIDs.
     */
    public void setMap(Map<UUID, UUID> map) { this.map = map; }
}
