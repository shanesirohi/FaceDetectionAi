open module nd4j.common {
    requires commons.io;
    requires org.apache.commons.compress;
    requires org.apache.commons.lang3;
    requires commons.math3;
    requires guava;
    requires jackson;
    requires slf4j.api;
    exports org.nd4j.common.base;
    exports org.nd4j.common.collection;
    exports org.nd4j.common.collections;
    exports org.nd4j.common.config;
    exports org.nd4j.common.function;
    exports org.nd4j.common.holder;
    exports org.nd4j.common.io;
    exports org.nd4j.common.loader;
    exports org.nd4j.common.primitives;
    exports org.nd4j.common.primitives.serde;
    exports org.nd4j.common.tools;
    exports org.nd4j.common.util;
    exports org.nd4j.common.validation;
}
Data
@Builder(toBuilder = true)
public class OpDeclarationDescriptor implements Serializable  {
    private String name;
    private int nIn,nOut,tArgs,iArgs;
    private boolean inplaceAble;
    private List<String> inArgNames;
    private List<String> outArgNames;
    private List<String> tArgNames;
    private List<String> iArgNames;
    private List<String> bArgNames;


    private OpDeclarationType opDeclarationType;
    @Builder.Default
    private Map<String,Boolean> argOptional = new HashMap<>();


    public enum OpDeclarationType {
        CUSTOM_OP_IMPL,
        BOOLEAN_OP_IMPL,
        LIST_OP_IMPL,
        LOGIC_OP_IMPL,
        OP_IMPL,
        DIVERGENT_OP_IMPL,
        CONFIGURABLE_OP_IMPL,
        REDUCTION_OP_IMPL,
        BROADCASTABLE_OP_IMPL,
        BROADCASTABLE_BOOL_OP_IMPL,
        LEGACY_XYZ,
        PLATFORM_IMPL,
        PLATFORM_TRANSFORM_STRICT_IMPL,
        PLATFORM_SCALAR_OP_IMPL,
        PLATFORM_CHECK
    }



    public void validate() {
        if(nIn >= 0 && nIn != inArgNames.size() && !isVariableInputSize()) {
            System.err.println("In arg names was not equal to number of inputs found for op " + name);
        }

        if(nOut >= 0 && nOut != outArgNames.size() && !isVariableOutputSize()) {
            System.err.println("Output arg names was not equal to number of outputs found for op " + name);
        }

        if(tArgs >= 0 && tArgs != tArgNames.size() && !isVariableTArgs()) {
            System.err.println("T arg names was not equal to number of T found for op " + name);
        }
        if(iArgs >= 0 && iArgs != iArgNames.size() && !isVariableIntArgs()) {
            System.err.println("Integer arg names was not equal to number of integer args found for op " + name);
        }
    }


    /**
     * Returns true if there is a variable number
     * of integer arguments for an op
     * @return
     */
    public boolean isVariableIntArgs() {
        return iArgs < 0;
    }

    /**
     * Returns true if there is a variable
     * number of t arguments for an op
     * @return
     */
    public boolean isVariableTArgs() {
        return tArgs < 0;
    }

    /**
     * Returns true if the number of outputs is variable size
     * @return
     */
    public boolean isVariableOutputSize() {
        return nOut < 0;
    }

    /**
     * Returns true if the number of
     * inputs is variable size
     * @return
     */
    public boolean isVariableInputSize() {
        return nIn < 0;
    }


}