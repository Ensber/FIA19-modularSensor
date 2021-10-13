<?php

namespace App\Entity;

use Doctrine\ORM\Mapping as ORM;

/**
 * Module
 *
 * @ORM\Table(name="Module", indexes={@ORM\Index(name="Module_ibfk_1", columns={"PL_ID"}), @ORM\Index(name="Module_ibfk_2", columns={"Typ_ID"})})
 * @ORM\Entity(repositoryClass="App\Repository\ModuleRepository")
 */
class Module
{
    /**
     * @var int
     *
     * @ORM\Column(name="Modul_ID", type="integer", nullable=false, options={"unsigned"=true})
     * @ORM\Id
     * @ORM\GeneratedValue(strategy="IDENTITY")
     */
    private $modulId;

    /**
     * @var bool
     *
     * @ORM\Column(name="Slot", type="boolean", nullable=false)
     */
    private $slot;

    /**
     * @var Platform
     *
     * @ORM\ManyToOne(targetEntity="Platform")
     * @ORM\JoinColumns({
     *   @ORM\JoinColumn(name="PL_ID", referencedColumnName="PL_ID")
     * })
     */
    private $pl;

    /**
     * @var Typ
     *
     * @ORM\ManyToOne(targetEntity="Typ")
     * @ORM\JoinColumns({
     *   @ORM\JoinColumn(name="Typ_ID", referencedColumnName="Typ_ID")
     * })
     */
    private $typ;

    /**
     * @return int
     */
    public function getModulId(): int
    {
        return $this->modulId;
    }

    /**
     * @param int $modulId
     */
    public function setModulId(int $modulId): void
    {
        $this->modulId = $modulId;
    }

    /**
     * @return bool
     */
    public function isSlot(): bool
    {
        return $this->slot;
    }

    /**
     * @param bool $slot
     */
    public function setSlot(bool $slot): void
    {
        $this->slot = $slot;
    }

    /**
     * @return Platform
     */
    public function getPl(): Platform
    {
        return $this->pl;
    }

    /**
     * @param Platform $pl
     */
    public function setPl(Platform $pl): void
    {
        $this->pl = $pl;
    }

    /**
     * @return Typ
     */
    public function getTyp(): Typ
    {
        return $this->typ;
    }

    /**
     * @param Typ $typ
     */
    public function setTyp(Typ $typ): void
    {
        $this->typ = $typ;
    }

}
