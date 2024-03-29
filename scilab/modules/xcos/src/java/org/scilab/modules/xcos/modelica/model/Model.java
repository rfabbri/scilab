/*
 * Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 * Copyright (C) 2010-2010 - DIGITEO - Clement DAVID <clement.david@scilab.org>
 * Copyright (C) 2011-2013 - Scilab Enterprises - Clement DAVID
 *
 * This file must be used under the terms of the CeCILL.
 * This source file is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at
 * http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.txt
 *
 */

package org.scilab.modules.xcos.modelica.model;

import java.util.ArrayList;
import java.util.List;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlType;

/**
 * Root of the modelica tree.
 *
 * <p>
 * Java class for Model complex type.
 *
 * <p>
 * The following schema fragment specifies the expected content contained within
 * this class.
 *
 * <pre>
 * &lt;complexType name="Model">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="name" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="model_info" type="{}Info" minOccurs="0"/>
 *         &lt;element name="identifiers" minOccurs="0">
 *           &lt;complexType>
 *             &lt;complexContent>
 *               &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *                 &lt;sequence>
 *                   &lt;element name="parameter" type="{http://www.w3.org/2001/XMLSchema}string" maxOccurs="unbounded" minOccurs="0"/>
 *                   &lt;element name="explicit_variable" type="{http://www.w3.org/2001/XMLSchema}string" maxOccurs="unbounded" minOccurs="0"/>
 *                   &lt;element name="implicit_variable" type="{http://www.w3.org/2001/XMLSchema}string" maxOccurs="unbounded" minOccurs="0"/>
 *                   &lt;element name="input" type="{http://www.w3.org/2001/XMLSchema}string" maxOccurs="unbounded" minOccurs="0"/>
 *                 &lt;/sequence>
 *               &lt;/restriction>
 *             &lt;/complexContent>
 *           &lt;/complexType>
 *         &lt;/element>
 *         &lt;element name="implicit_relations" minOccurs="0">
 *           &lt;complexType>
 *             &lt;complexContent>
 *               &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *                 &lt;sequence>
 *                   &lt;element name="implicit_relation" maxOccurs="unbounded" minOccurs="0">
 *                     &lt;complexType>
 *                       &lt;complexContent>
 *                         &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *                           &lt;sequence>
 *                             &lt;element name="implicit_variable" type="{http://www.w3.org/2001/XMLSchema}string" maxOccurs="unbounded" minOccurs="0"/>
 *                             &lt;element name="input" type="{http://www.w3.org/2001/XMLSchema}string" maxOccurs="unbounded" minOccurs="0"/>
 *                           &lt;/sequence>
 *                         &lt;/restriction>
 *                       &lt;/complexContent>
 *                     &lt;/complexType>
 *                   &lt;/element>
 *                 &lt;/sequence>
 *               &lt;/restriction>
 *             &lt;/complexContent>
 *           &lt;/complexType>
 *         &lt;/element>
 *         &lt;element name="explicit_relations" minOccurs="0">
 *           &lt;complexType>
 *             &lt;complexContent>
 *               &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *                 &lt;sequence>
 *                   &lt;element name="explicit_relation" maxOccurs="unbounded" minOccurs="0">
 *                     &lt;complexType>
 *                       &lt;complexContent>
 *                         &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *                           &lt;sequence>
 *                             &lt;element name="explicit_variable" type="{http://www.w3.org/2001/XMLSchema}string" maxOccurs="unbounded" minOccurs="0"/>
 *                           &lt;/sequence>
 *                         &lt;/restriction>
 *                       &lt;/complexContent>
 *                     &lt;/complexType>
 *                   &lt;/element>
 *                 &lt;/sequence>
 *               &lt;/restriction>
 *             &lt;/complexContent>
 *           &lt;/complexType>
 *         &lt;/element>
 *         &lt;element name="outputs" minOccurs="0">
 *           &lt;complexType>
 *             &lt;complexContent>
 *               &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *                 &lt;sequence>
 *                   &lt;element name="output" type="{}Output" maxOccurs="unbounded" minOccurs="0"/>
 *                 &lt;/sequence>
 *               &lt;/restriction>
 *             &lt;/complexContent>
 *           &lt;/complexType>
 *         &lt;/element>
 *         &lt;element name="elements" minOccurs="0">
 *           &lt;complexType>
 *             &lt;complexContent>
 *               &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *                 &lt;sequence>
 *                   &lt;element name="struct" type="{}Struct" maxOccurs="unbounded" minOccurs="0"/>
 *                 &lt;/sequence>
 *               &lt;/restriction>
 *             &lt;/complexContent>
 *           &lt;/complexType>
 *         &lt;/element>
 *         &lt;element name="equations" minOccurs="0">
 *           &lt;complexType>
 *             &lt;complexContent>
 *               &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *                 &lt;sequence>
 *                   &lt;element name="equation" type="{}ModelicaValue" maxOccurs="unbounded" minOccurs="0"/>
 *                 &lt;/sequence>
 *               &lt;/restriction>
 *             &lt;/complexContent>
 *           &lt;/complexType>
 *         &lt;/element>
 *         &lt;element name="when_clauses" minOccurs="0">
 *           &lt;simpleType>
 *             &lt;restriction base="{http://www.w3.org/2001/XMLSchema}string">
 *             &lt;/restriction>
 *           &lt;/simpleType>
 *         &lt;/element>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 *
 *
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "Model", propOrder = { "name", "modelInfo", "identifiers", "implicitRelations", "explicitRelations", "outputs", "elements", "equations",
                                       "whenClauses"
                                     })
public class Model {

    protected String name;
    @XmlElement(name = "model_info")
    protected Info modelInfo;
    protected Model.Identifiers identifiers;
    @XmlElement(name = "implicit_relations")
    protected Model.ImplicitRelations implicitRelations;
    @XmlElement(name = "explicit_relations")
    protected Model.ExplicitRelations explicitRelations;
    protected Model.Outputs outputs;
    protected Model.Elements elements;
    protected Model.Equations equations;
    @XmlElement(name = "when_clauses")
    protected String whenClauses;

    /**
     * Gets the value of the name property.
     *
     * @return possible object is {@link String }
     *
     */
    public String getName() {
        return name;
    }

    /**
     * Sets the value of the name property.
     *
     * @param value
     *            allowed object is {@link String }
     *
     */
    public void setName(String value) {
        this.name = value;
    }

    /**
     * Gets the value of the modelInfo property.
     *
     * @return possible object is {@link Info }
     *
     */
    public Info getModelInfo() {
        return modelInfo;
    }

    /**
     * Sets the value of the modelInfo property.
     *
     * @param value
     *            allowed object is {@link Info }
     *
     */
    public void setModelInfo(Info value) {
        this.modelInfo = value;
    }

    /**
     * Gets the value of the identifiers property.
     *
     * @return possible object is {@link Model.Identifiers }
     *
     */
    public Model.Identifiers getIdentifiers() {
        return identifiers;
    }

    /**
     * Sets the value of the identifiers property.
     *
     * @param value
     *            allowed object is {@link Model.Identifiers }
     *
     */
    public void setIdentifiers(Model.Identifiers value) {
        this.identifiers = value;
    }

    /**
     * Gets the value of the implicitRelations property.
     *
     * @return possible object is {@link Model.ImplicitRelations }
     *
     */
    public Model.ImplicitRelations getImplicitRelations() {
        return implicitRelations;
    }

    /**
     * Sets the value of the implicitRelations property.
     *
     * @param value
     *            allowed object is {@link Model.ImplicitRelations }
     *
     */
    public void setImplicitRelations(Model.ImplicitRelations value) {
        this.implicitRelations = value;
    }

    /**
     * Gets the value of the explicitRelations property.
     *
     * @return possible object is {@link Model.ExplicitRelations }
     *
     */
    public Model.ExplicitRelations getExplicitRelations() {
        return explicitRelations;
    }

    /**
     * Sets the value of the explicitRelations property.
     *
     * @param value
     *            allowed object is {@link Model.ExplicitRelations }
     *
     */
    public void setExplicitRelations(Model.ExplicitRelations value) {
        this.explicitRelations = value;
    }

    /**
     * Gets the value of the outputs property.
     *
     * @return possible object is {@link Model.Outputs }
     *
     */
    public Model.Outputs getOutputs() {
        return outputs;
    }

    /**
     * Sets the value of the outputs property.
     *
     * @param value
     *            allowed object is {@link Model.Outputs }
     *
     */
    public void setOutputs(Model.Outputs value) {
        this.outputs = value;
    }

    /**
     * Gets the value of the elements property.
     *
     * @return possible object is {@link Model.Elements }
     *
     */
    public Model.Elements getElements() {
        return elements;
    }

    /**
     * Sets the value of the elements property.
     *
     * @param value
     *            allowed object is {@link Model.Elements }
     *
     */
    public void setElements(Model.Elements value) {
        this.elements = value;
    }

    /**
     * Gets the value of the equations property.
     *
     * @return possible object is {@link Model.Equations }
     *
     */
    public Model.Equations getEquations() {
        return equations;
    }

    /**
     * Sets the value of the equations property.
     *
     * @param value
     *            allowed object is {@link Model.Equations }
     *
     */
    public void setEquations(Model.Equations value) {
        this.equations = value;
    }

    /**
     * Gets the value of the whenClauses property.
     *
     * @return possible object is {@link String }
     *
     */
    public String getWhenClauses() {
        return whenClauses;
    }

    /**
     * Sets the value of the whenClauses property.
     *
     * @param value
     *            allowed object is {@link String }
     *
     */
    public void setWhenClauses(String value) {
        this.whenClauses = value;
    }

    /**
     * <p>
     * Java class for anonymous complex type.
     *
     * <p>
     * The following schema fragment specifies the expected content contained
     * within this class.
     *
     * <pre>
     * &lt;complexType>
     *   &lt;complexContent>
     *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
     *       &lt;sequence>
     *         &lt;element name="struct" type="{}Struct" maxOccurs="unbounded" minOccurs="0"/>
     *       &lt;/sequence>
     *     &lt;/restriction>
     *   &lt;/complexContent>
     * &lt;/complexType>
     * </pre>
     *
     *
     */
    @XmlAccessorType(XmlAccessType.FIELD)
    @XmlType(name = "", propOrder = { "struct" })
    public static class Elements {

        @XmlElement(nillable = true)
        protected List<Struct> struct;

        /**
         * Gets the value of the struct property.
         *
         * <p>
         * This accessor method returns a reference to the live list, not a
         * snapshot. Therefore any modification you make to the returned list
         * will be present inside the JAXB object. This is why there is not a
         * <CODE>set</CODE> method for the struct property.
         *
         * <p>
         * For example, to add a new item, do as follows:
         *
         * <pre>
         * getStruct().add(newItem);
         * </pre>
         *
         *
         * <p>
         * Objects of the following type(s) are allowed in the list
         * {@link Struct }
         *
         *
         */
        public List<Struct> getStruct() {
            if (struct == null) {
                struct = new ArrayList<Struct>();
            }
            return this.struct;
        }

    }

    /**
     * <p>
     * Java class for anonymous complex type.
     *
     * <p>
     * The following schema fragment specifies the expected content contained
     * within this class.
     *
     * <pre>
     * &lt;complexType>
     *   &lt;complexContent>
     *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
     *       &lt;sequence>
     *         &lt;element name="equation" type="{}ModelicaValue" maxOccurs="unbounded" minOccurs="0"/>
     *       &lt;/sequence>
     *     &lt;/restriction>
     *   &lt;/complexContent>
     * &lt;/complexType>
     * </pre>
     *
     *
     */
    @XmlAccessorType(XmlAccessType.FIELD)
    @XmlType(name = "", propOrder = { "equation" })
    public static class Equations {

        @XmlElement(nillable = true)
        protected List<ModelicaValue> equation;

        /**
         * Gets the value of the equation property.
         *
         * <p>
         * This accessor method returns a reference to the live list, not a
         * snapshot. Therefore any modification you make to the returned list
         * will be present inside the JAXB object. This is why there is not a
         * <CODE>set</CODE> method for the equation property.
         *
         * <p>
         * For example, to add a new item, do as follows:
         *
         * <pre>
         * getEquation().add(newItem);
         * </pre>
         *
         *
         * <p>
         * Objects of the following type(s) are allowed in the list
         * {@link ModelicaValue }
         *
         *
         */
        public List<ModelicaValue> getEquation() {
            if (equation == null) {
                equation = new ArrayList<ModelicaValue>();
            }
            return this.equation;
        }

    }

    /**
     * Wrapper around the explicit variables list.
     *
     * <p>
     * Java class for anonymous complex type.
     *
     * <p>
     * The following schema fragment specifies the expected content contained
     * within this class.
     *
     * <pre>
     * &lt;complexType>
     *   &lt;complexContent>
     *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
     *       &lt;sequence>
     *         &lt;element name="explicit_relation" maxOccurs="unbounded" minOccurs="0">
     *           &lt;complexType>
     *             &lt;complexContent>
     *               &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
     *                 &lt;sequence>
     *                   &lt;element name="explicit_variable" type="{http://www.w3.org/2001/XMLSchema}string" maxOccurs="unbounded" minOccurs="0"/>
     *                 &lt;/sequence>
     *               &lt;/restriction>
     *             &lt;/complexContent>
     *           &lt;/complexType>
     *         &lt;/element>
     *       &lt;/sequence>
     *     &lt;/restriction>
     *   &lt;/complexContent>
     * &lt;/complexType>
     * </pre>
     *
     *
     */
    @XmlAccessorType(XmlAccessType.FIELD)
    @XmlType(name = "", propOrder = { "explicitRelation" })
    public static class ExplicitRelations {

        @XmlElement(name = "explicit_relation")
        protected List<Model.ExplicitRelations.ExplicitRelation> explicitRelation;

        /**
         * Gets the value of the explicitRelation property.
         *
         * <p>
         * This accessor method returns a reference to the live list, not a
         * snapshot. Therefore any modification you make to the returned list
         * will be present inside the JAXB object. This is why there is not a
         * <CODE>set</CODE> method for the explicitRelation property.
         *
         * <p>
         * For example, to add a new item, do as follows:
         *
         * <pre>
         * getExplicitRelation().add(newItem);
         * </pre>
         *
         *
         * <p>
         * Objects of the following type(s) are allowed in the list
         * {@link Model.ExplicitRelations.ExplicitRelation }
         *
         *
         */
        public List<Model.ExplicitRelations.ExplicitRelation> getExplicitRelation() {
            if (explicitRelation == null) {
                explicitRelation = new ArrayList<Model.ExplicitRelations.ExplicitRelation>();
            }
            return this.explicitRelation;
        }

        /**
         * <p>
         * Java class for anonymous complex type.
         *
         * <p>
         * The following schema fragment specifies the expected content
         * contained within this class.
         *
         * <pre>
         * &lt;complexType>
         *   &lt;complexContent>
         *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
         *       &lt;sequence>
         *         &lt;element name="explicit_variable" type="{http://www.w3.org/2001/XMLSchema}string" maxOccurs="unbounded" minOccurs="0"/>
         *       &lt;/sequence>
         *     &lt;/restriction>
         *   &lt;/complexContent>
         * &lt;/complexType>
         * </pre>
         *
         *
         */
        @XmlAccessorType(XmlAccessType.FIELD)
        @XmlType(name = "", propOrder = { "explicitVariable" })
        public static class ExplicitRelation {

            @XmlElement(name = "explicit_variable")
            protected List<String> explicitVariable;

            /**
             * Gets the value of the explicitVariable property.
             *
             * <p>
             * This accessor method returns a reference to the live list, not a
             * snapshot. Therefore any modification you make to the returned
             * list will be present inside the JAXB object. This is why there is
             * not a <CODE>set</CODE> method for the explicitVariable property.
             *
             * <p>
             * For example, to add a new item, do as follows:
             *
             * <pre>
             * getExplicitVariable().add(newItem);
             * </pre>
             *
             *
             * <p>
             * Objects of the following type(s) are allowed in the list
             * {@link String }
             *
             *
             */
            public List<String> getExplicitVariable() {
                if (explicitVariable == null) {
                    explicitVariable = new ArrayList<String>();
                }
                return this.explicitVariable;
            }

        }

    }

    /**
     * Describe any model identifier.
     *
     * <p>
     * Java class for anonymous complex type.
     *
     * <p>
     * The following schema fragment specifies the expected content contained
     * within this class.
     *
     * <pre>
     * &lt;complexType>
     *   &lt;complexContent>
     *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
     *       &lt;sequence>
     *         &lt;element name="parameter" type="{http://www.w3.org/2001/XMLSchema}string" maxOccurs="unbounded" minOccurs="0"/>
     *         &lt;element name="explicit_variable" type="{http://www.w3.org/2001/XMLSchema}string" maxOccurs="unbounded" minOccurs="0"/>
     *         &lt;element name="implicit_variable" type="{http://www.w3.org/2001/XMLSchema}string" maxOccurs="unbounded" minOccurs="0"/>
     *         &lt;element name="input" type="{http://www.w3.org/2001/XMLSchema}string" maxOccurs="unbounded" minOccurs="0"/>
     *       &lt;/sequence>
     *     &lt;/restriction>
     *   &lt;/complexContent>
     * &lt;/complexType>
     * </pre>
     *
     *
     */
    @XmlAccessorType(XmlAccessType.FIELD)
    @XmlType(name = "", propOrder = { "parameter", "explicitVariable", "implicitVariable", "input" })
    public static class Identifiers {

        @XmlElement(nillable = true)
        protected List<String> parameter;
        @XmlElement(name = "explicit_variable")
        protected List<String> explicitVariable;
        @XmlElement(name = "implicit_variable")
        protected List<String> implicitVariable;
        protected List<String> input;

        /**
         * Gets the value of the parameter property.
         *
         * <p>
         * This accessor method returns a reference to the live list, not a
         * snapshot. Therefore any modification you make to the returned list
         * will be present inside the JAXB object. This is why there is not a
         * <CODE>set</CODE> method for the parameter property.
         *
         * <p>
         * For example, to add a new item, do as follows:
         *
         * <pre>
         * getParameter().add(newItem);
         * </pre>
         *
         *
         * <p>
         * Objects of the following type(s) are allowed in the list
         * {@link String }
         *
         *
         */
        public List<String> getParameter() {
            if (parameter == null) {
                parameter = new ArrayList<String>();
            }
            return this.parameter;
        }

        /**
         * Gets the value of the explicitVariable property.
         *
         * <p>
         * This accessor method returns a reference to the live list, not a
         * snapshot. Therefore any modification you make to the returned list
         * will be present inside the JAXB object. This is why there is not a
         * <CODE>set</CODE> method for the explicitVariable property.
         *
         * <p>
         * For example, to add a new item, do as follows:
         *
         * <pre>
         * getExplicitVariable().add(newItem);
         * </pre>
         *
         *
         * <p>
         * Objects of the following type(s) are allowed in the list
         * {@link String }
         *
         *
         */
        public List<String> getExplicitVariable() {
            if (explicitVariable == null) {
                explicitVariable = new ArrayList<String>();
            }
            return this.explicitVariable;
        }

        /**
         * Gets the value of the implicitVariable property.
         *
         * <p>
         * This accessor method returns a reference to the live list, not a
         * snapshot. Therefore any modification you make to the returned list
         * will be present inside the JAXB object. This is why there is not a
         * <CODE>set</CODE> method for the implicitVariable property.
         *
         * <p>
         * For example, to add a new item, do as follows:
         *
         * <pre>
         * getImplicitVariable().add(newItem);
         * </pre>
         *
         *
         * <p>
         * Objects of the following type(s) are allowed in the list
         * {@link String }
         *
         *
         */
        public List<String> getImplicitVariable() {
            if (implicitVariable == null) {
                implicitVariable = new ArrayList<String>();
            }
            return this.implicitVariable;
        }

        /**
         * Gets the value of the input property.
         *
         * <p>
         * This accessor method returns a reference to the live list, not a
         * snapshot. Therefore any modification you make to the returned list
         * will be present inside the JAXB object. This is why there is not a
         * <CODE>set</CODE> method for the input property.
         *
         * <p>
         * For example, to add a new item, do as follows:
         *
         * <pre>
         * getInput().add(newItem);
         * </pre>
         *
         *
         * <p>
         * Objects of the following type(s) are allowed in the list
         * {@link String }
         *
         *
         */
        public List<String> getInput() {
            if (input == null) {
                input = new ArrayList<String>();
            }
            return this.input;
        }

    }

    /**
     * Wrapper around the implicit (and inputs) variables list.
     *
     * <p>
     * Java class for anonymous complex type.
     *
     * <p>
     * The following schema fragment specifies the expected content contained
     * within this class.
     *
     * <pre>
     * &lt;complexType>
     *   &lt;complexContent>
     *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
     *       &lt;sequence>
     *         &lt;element name="implicit_relation" maxOccurs="unbounded" minOccurs="0">
     *           &lt;complexType>
     *             &lt;complexContent>
     *               &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
     *                 &lt;sequence>
     *                   &lt;element name="implicit_variable" type="{http://www.w3.org/2001/XMLSchema}string" maxOccurs="unbounded" minOccurs="0"/>
     *                   &lt;element name="input" type="{http://www.w3.org/2001/XMLSchema}string" maxOccurs="unbounded" minOccurs="0"/>
     *                 &lt;/sequence>
     *               &lt;/restriction>
     *             &lt;/complexContent>
     *           &lt;/complexType>
     *         &lt;/element>
     *       &lt;/sequence>
     *     &lt;/restriction>
     *   &lt;/complexContent>
     * &lt;/complexType>
     * </pre>
     *
     *
     */
    @XmlAccessorType(XmlAccessType.FIELD)
    @XmlType(name = "", propOrder = { "implicitRelation" })
    public static class ImplicitRelations {

        @XmlElement(name = "implicit_relation")
        protected List<Model.ImplicitRelations.ImplicitRelation> implicitRelation;

        /**
         * Gets the value of the implicitRelation property.
         *
         * <p>
         * This accessor method returns a reference to the live list, not a
         * snapshot. Therefore any modification you make to the returned list
         * will be present inside the JAXB object. This is why there is not a
         * <CODE>set</CODE> method for the implicitRelation property.
         *
         * <p>
         * For example, to add a new item, do as follows:
         *
         * <pre>
         * getImplicitRelation().add(newItem);
         * </pre>
         *
         *
         * <p>
         * Objects of the following type(s) are allowed in the list
         * {@link Model.ImplicitRelations.ImplicitRelation }
         *
         *
         */
        public List<Model.ImplicitRelations.ImplicitRelation> getImplicitRelation() {
            if (implicitRelation == null) {
                implicitRelation = new ArrayList<Model.ImplicitRelations.ImplicitRelation>();
            }
            return this.implicitRelation;
        }

        /**
         * <p>
         * Java class for anonymous complex type.
         *
         * <p>
         * The following schema fragment specifies the expected content
         * contained within this class.
         *
         * <pre>
         * &lt;complexType>
         *   &lt;complexContent>
         *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
         *       &lt;sequence>
         *         &lt;element name="implicit_variable" type="{http://www.w3.org/2001/XMLSchema}string" maxOccurs="unbounded" minOccurs="0"/>
         *         &lt;element name="input" type="{http://www.w3.org/2001/XMLSchema}string" maxOccurs="unbounded" minOccurs="0"/>
         *       &lt;/sequence>
         *     &lt;/restriction>
         *   &lt;/complexContent>
         * &lt;/complexType>
         * </pre>
         *
         *
         */
        @XmlAccessorType(XmlAccessType.FIELD)
        @XmlType(name = "", propOrder = { "implicitVariable", "input" })
        public static class ImplicitRelation {

            @XmlElement(name = "implicit_variable")
            protected List<String> implicitVariable;
            protected List<String> input;

            /**
             * Gets the value of the implicitVariable property.
             *
             * <p>
             * This accessor method returns a reference to the live list, not a
             * snapshot. Therefore any modification you make to the returned
             * list will be present inside the JAXB object. This is why there is
             * not a <CODE>set</CODE> method for the implicitVariable property.
             *
             * <p>
             * For example, to add a new item, do as follows:
             *
             * <pre>
             * getImplicitVariable().add(newItem);
             * </pre>
             *
             *
             * <p>
             * Objects of the following type(s) are allowed in the list
             * {@link String }
             *
             *
             */
            public List<String> getImplicitVariable() {
                if (implicitVariable == null) {
                    implicitVariable = new ArrayList<String>();
                }
                return this.implicitVariable;
            }

            /**
             * Gets the value of the input property.
             *
             * <p>
             * This accessor method returns a reference to the live list, not a
             * snapshot. Therefore any modification you make to the returned
             * list will be present inside the JAXB object. This is why there is
             * not a <CODE>set</CODE> method for the input property.
             *
             * <p>
             * For example, to add a new item, do as follows:
             *
             * <pre>
             * getInput().add(newItem);
             * </pre>
             *
             *
             * <p>
             * Objects of the following type(s) are allowed in the list
             * {@link String }
             *
             *
             */
            public List<String> getInput() {
                if (input == null) {
                    input = new ArrayList<String>();
                }
                return this.input;
            }

        }

    }

    /**
     * Wrapper around the {@link Output} list.
     *
     * <p>
     * Java class for anonymous complex type.
     *
     * <p>
     * The following schema fragment specifies the expected content contained
     * within this class.
     *
     * <pre>
     * &lt;complexType>
     *   &lt;complexContent>
     *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
     *       &lt;sequence>
     *         &lt;element name="output" type="{}Output" maxOccurs="unbounded" minOccurs="0"/>
     *       &lt;/sequence>
     *     &lt;/restriction>
     *   &lt;/complexContent>
     * &lt;/complexType>
     * </pre>
     *
     *
     */
    @XmlAccessorType(XmlAccessType.FIELD)
    @XmlType(name = "", propOrder = { "output" })
    public static class Outputs {

        protected List<Output> output;

        /**
         * Gets the value of the output property.
         *
         * <p>
         * This accessor method returns a reference to the live list, not a
         * snapshot. Therefore any modification you make to the returned list
         * will be present inside the JAXB object. This is why there is not a
         * <CODE>set</CODE> method for the output property.
         *
         * <p>
         * For example, to add a new item, do as follows:
         *
         * <pre>
         * getOutput().add(newItem);
         * </pre>
         *
         *
         * <p>
         * Objects of the following type(s) are allowed in the list
         * {@link Output }
         *
         *
         */
        public List<Output> getOutput() {
            if (output == null) {
                output = new ArrayList<Output>();
            }
            return this.output;
        }

    }

    /*
     * Overriden methods
     */

    /**
     * @return the name
     * @see java.lang.Object#toString()
     */
    @Override
    public String toString() {
        return getName();
    }
}
